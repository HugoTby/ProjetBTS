#include "callAPI.h"
#include "inveo.h"
callAPI::callAPI(QObject* parent)
    : QObject(parent)
{
    serial = new QSerialPort(this);
    timer = new QTimer(this);
    QString port = "COM7";
    serial->setPortName(port);
    serial->setBaudRate(QSerialPort::Baud9600);
    // Ouvrir le port s�rie en mode �criture seule
    if (serial->open(QIODevice::WriteOnly))
    {
        qDebug() << "port serie ouvert";
    }
    else
    {
        qDebug() << "Erreur d'ouverture du port s�rie :" << serial->errorString();
    }
   
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &callAPI::onFinishedRequest);
    connect(this, &callAPI::onAPIReply, this, &callAPI::GetInfosQuotaHeures);
    QObject::connect(this, &callAPI::onBoxDispoReceived, &callAPI::allumerLed);

}

void callAPI::selectWhereUID(QString uid)
{
    QUrl url("http://192.168.65.105:5001/utilisateurs/badge_utilisateur");

    // Cr�er un objet QUrlQuery pour ajouter le param�tre de requ�te
    QUrlQuery query;
    query.addQueryItem("badge_utilisateur", uid);

    // Ajouter le param�tre de requ�te � l'URL
    url.setQuery(query);

    QNetworkRequest request(url);

    // Utilisez la m�thode GET pour r�cup�rer les informations
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

void callAPI::verifyBoxUsedByUser(QString uid)
{
    QUrl url("http://192.168.65.105:5001/utilisateurs/badge_utilisateur/boxUsed/" + uid);
    QUrlQuery query;
    url.setQuery(query);
    QNetworkRequest request(url);
    manager.get(request);
}

void callAPI::GetInfosQuotaHeures(QNetworkReply* reply, QByteArray data)
{
    // Parser la r�ponse JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    // R�cup�rer les valeurs des cl�s dans l'objet JSON
    float quota = jsonObj["quota_utilisateur"].toVariant().toFloat();
    int boxDispo = jsonObj["freeBox"].toInt();
    QDateTime heure;
    if (!jsonObj["heure_depot_occupation"].isNull()) {
        QString dateTimeStr = jsonObj["heure_depot_occupation"].toString();
        heure = QDateTime::fromString(dateTimeStr, "yyyy-MM-dd hh:mm:ss");
    }

    // V�rifier les conditions d'acc�s
    bool userCanAccessBox;
    if (quota >= 1 && (heure.isNull() || heure.secsTo(QDateTime::currentDateTime()) >= 90000) && boxDispo != NULL) {
        userCanAccessBox = true;
        qDebug() << "l'utilisateur dispose d'un quota suffisant et a d�pos� pour la derni�re fois un v�hicule il y'a plus de 25 heures, voici le box que vous pouvez utiliser :" + QString::number(boxDispo);
        emit onBoxDispoReceived(boxDispo);
    }
    else {
        userCanAccessBox = false;
        qDebug() << "conditions non respect�es";
    }
}

void callAPI::allumerLed(int boxDispo)
{
    QString command = "LEDON_PLAN" + QString::number(boxDispo + 1);
    // �crire la commande sur le port s�rie
    serial->write(command.toLatin1());
    qDebug() << command;
    // Attendre que la commande soit envoy�e compl�tement
    serial->waitForBytesWritten(1000);
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