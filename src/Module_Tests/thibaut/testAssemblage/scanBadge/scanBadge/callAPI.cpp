#include "callAPI.h"

callAPI::callAPI(QObject* parent)
    : QObject(parent)
{
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &callAPI::onFinishedRequest);
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

void callAPI::insertUser(QString uid, QString prenom, QString nom, QString classe, QString tel, QString mail, QString password, QString infos, float quota)
{
    QString quota_str = QString::number(quota);
    QUrl url("http://192.168.65.105:5001/utilisateurs");

    QJsonObject jsonObject;
    jsonObject.insert("badge_utilisateur", uid);
    jsonObject.insert("nom_utilisateur", nom);
    jsonObject.insert("prenom_utilisateur", prenom);
    jsonObject.insert("classe_utilisateur", classe);
    jsonObject.insert("password_utilisateur", password);
    jsonObject.insert("telephone_utilisateur", tel);
    jsonObject.insert("mail_utilisateur", mail);
    jsonObject.insert("quota_utilisateur", quota_str);

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = manager.post(request, jsonData);

}

bool callAPI::checkTimeandQuota(QString uid)
{
    QUrl url("http://192.168.65.105:5001/utilisateurs/badge_utilisateur/quota-depot/" + uid);
    QUrlQuery query;
    url.setQuery(query);
    QNetworkRequest request(url);
    manager.get(request);
    return false;
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