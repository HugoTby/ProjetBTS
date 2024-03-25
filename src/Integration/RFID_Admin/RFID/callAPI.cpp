#include "callAPI.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery>

callAPI::callAPI(QObject* parent)
    : QObject(parent)
{
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &callAPI::onFinishedRequest);
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

void callAPI::onFinishedRequest(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        emit onAPIReply(reply, responseData);
    }
    else {
        emit onAPIFailed(reply);
    }

    reply->deleteLater();
}