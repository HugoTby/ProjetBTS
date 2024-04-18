#include "APIUtilisateurReplyHandler.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantMap>

APIUtilisateurReplyHandler::APIUtilisateurReplyHandler()
	: APIReplyHandler("/utilisateurs")
{
}

void APIUtilisateurReplyHandler::onGetReply(QByteArray responseData)
{
	qInfo() << "R�cup�ration des informations r�ussie";
    qInfo() << responseData;
    
    /*QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonArray jsonArray = jsonDoc.array();

    for (const QJsonValue& value : jsonArray) {
        QJsonObject jsonObject = value.toObject();
        QVariantMap variantMap = jsonObject.toVariantMap();

        // Acc�der aux valeurs de la carte de variantes
        int id_utilisateur = variantMap["id_utilisateur"].toInt();
        bool isadmin_utilisateur = variantMap["isadmin_utilisateur"].toBool();
        QString nom_utilisateur = variantMap["nom_utilisateur"].toString();
        QString prenom_utilisateur = variantMap["prenom_utilisateur"].toString();
        QString classe_utilisateur = variantMap["classe_utilisateur"].toString();
        QString badge_utilisateur = variantMap["badge_utilisateur"].toString();
        QString photo_utilisateur = variantMap["photo_utilisateur"].toString();
        QString password_utilisateur = variantMap["password_utilisateur"].toString();
        QString telephone_utilisateur = variantMap["telephone_utilisateur"].toString();
        QString mail_utilisateur = variantMap["mail_utilisateur"].toString();
        QVariant infos_utilisateur = variantMap["infos_utilisateur"];
        double quota_utilisateur = variantMap["quota_utilisateur"].toDouble();

        // Faire quelque chose avec les donn�es
        qDebug() << nom_utilisateur;
        qDebug() << telephone_utilisateur;
        
    }
*/
}

void APIUtilisateurReplyHandler::onPutReply(QByteArray responseData)
{
	qInfo() << "Utilisateur modifi� avec succ�s";
}

void APIUtilisateurReplyHandler::onPostReply(QByteArray responseData)
{
	qInfo() << "Utilisateur cr�� avec succ�s";
	qInfo() << responseData;
}

void APIUtilisateurReplyHandler::onDeleteReply(QByteArray responseData)
{
	qInfo() << "Utilisateur supprim� avec succ�s";
}
