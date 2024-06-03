#include "callAPI.h"

callAPI::callAPI(QObject* parent)
    : QObject(parent)
{
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &callAPI::onFinishedRequest);
    connect(this, &callAPI::onAPIReply, this, &callAPI::GetInfosQuotaHeures);
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
    QUrl url("http://192.168.65.105:5001/utilisateurs/badge_utilisateur/quota-depot/" + uid);
    QUrlQuery query;
    url.setQuery(query);
    QNetworkRequest request(url);
    manager.get(request);
}

void callAPI::GetInfosQuotaHeures(QNetworkReply* reply, QByteArray data)
{
    // Parser la réponse JSON
    qDebug() << data;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonDoc.object();

    // Récupérer les valeurs des clés dans l'objet JSON
    float quota = jsonObj["quota_utilisateur"].toVariant().toFloat();
    QDateTime heure;
    if (!jsonObj["heure_depot_occupation"].isNull()) {
        QString dateTimeStr = jsonObj["heure_depot_occupation"].toString();
        heure = QDateTime::fromString(dateTimeStr, "yyyy-MM-dd hh:mm:ss");
    }

    // Vérifier les conditions d'accès
    bool userCanAccessBox;
    qDebug() << quota;
    if (quota >= 1 && (heure.isNull() || heure.secsTo(QDateTime::currentDateTime()) >= 90000)) {
        userCanAccessBox = true;
        qDebug() << "l'utilisateur dispose d'un quota suffisant et a déposé pour la dernière fois un véhicule il y'a plus de 25 heures";
    }
    else {
        userCanAccessBox = false;
        qDebug() << "conditions non respectées";
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