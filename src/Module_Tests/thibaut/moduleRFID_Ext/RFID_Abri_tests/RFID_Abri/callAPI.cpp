#include "callAPI.h"
#include "inveo.h"
callAPI::callAPI(QObject* parent)
    : QObject(parent)
{
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &callAPI::onFinishedRequest);
    connect(this, &callAPI::onAPIReply, this, &callAPI::GetInfosQuotaHeures);
    QObject::connect(this, &callAPI::onBoxDispoReceived, &callAPI::allumerLed);
}

void callAPI::selectWhereUID(QString uid)
{
    QUrl url("http://192.168.65.105:5001/utilisateurs/badge_utilisateur");

    // Créer un objet QUrlQuery pour ajouter le paramètre de requête
    QUrlQuery query;
    query.addQueryItem("badge_utilisateur", uid);

    // Ajouter le paramètre de requête à l'URL
    url.setQuery(query);

    QNetworkRequest request(url);

    // Utilisez la méthode GET pour récupérer les informations
    manager.get(request);
}

void callAPI::checkTimeandQuota(QString uid)
{
    QUrl url("http://192.168.65.105:5001/utilisateurs/badge_utilisateur/quota-depot-freeboxs/" + uid);
    QUrlQuery query;
    url.setQuery(query);
    QNetworkRequest request(url);
    manager.get(request);
}

void callAPI::GetInfosQuotaHeures(QNetworkReply* reply, QByteArray data)
{
    // Parser la réponse JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    // Récupérer les valeurs des clés dans l'objet JSON
    float quota = jsonObj["quota_utilisateur"].toVariant().toFloat();
    int boxDispo = jsonObj["freeBox"].toInt();
    QDateTime heure;
    if (!jsonObj["heure_depot_occupation"].isNull()) {
        QString dateTimeStr = jsonObj["heure_depot_occupation"].toString();
        heure = QDateTime::fromString(dateTimeStr, "yyyy-MM-dd hh:mm:ss");
    }

    // Vérifier les conditions d'accès
    bool userCanAccessBox;
    if (quota >= 1 && (heure.isNull() || heure.secsTo(QDateTime::currentDateTime()) >= 90000) && boxDispo != NULL) {
        userCanAccessBox = true;
        qDebug() << "l'utilisateur dispose d'un quota suffisant et a déposé pour la dernière fois un véhicule il y'a plus de 25 heures, voici le box que vous pouvez utiliser :" + QString::number(boxDispo);
        emit onBoxDispoReceived(boxDispo);
    }
    else {
        userCanAccessBox = false;
        qDebug() << "conditions non respectées";
    }
}

void callAPI::allumerLed(int boxDispo)
{
    serial = new QSerialPort(this);
    QString port = "COM7";
    serial->setPortName(port);
    serial->setBaudRate(QSerialPort::Baud9600);
    // Ouvrir le port série en mode écriture seule
    if (serial->open(QIODevice::WriteOnly))
    {
        // Convertir la commande en QByteArray pour l'envoyer sur le port série
        QString command = "LEDON_PLAN" + QString::number(boxDispo + 1) + "\r\n";
        qDebug() << command;
        //qDebug() << "caca";
        // Écrire la commande sur le port série
        serial->write(command.toLatin1());

        // Attendre que la commande soit envoyée complètement
        serial->waitForBytesWritten(1000);

        // Fermer le port série
        serial->close();
    }
    else
    {
        // Gérer l'erreur d'ouverture du port série
        qDebug() << "Erreur d'ouverture du port série :" << serial->errorString();
    }
}

void callAPI::onFinishedRequest(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        qDebug() << jsonObject;
        emit onAPIReply(reply, responseData);
    }
    else {
        qDebug() << "Error:" << reply->errorString();
        emit onAPIFailed(reply);
    }
    reply->deleteLater();
}