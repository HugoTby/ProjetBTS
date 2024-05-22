#include "utilisateur.h"
#include <qDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


QList<utilisateur> utilisateur::toUncypherJSON(const QByteArray& jsonData)
{
    QList<utilisateur> userList;

    // Parse la réponse JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    // Vérifie si le parsing a réussi et si la réponse contient un tableau
    if (!jsonDoc.isNull() && jsonDoc.isArray()) {
        // Parcourt chaque élément du tableau JSON
        for (const QJsonValue& value : jsonDoc.array()) {
            if (value.isObject()) {
                utilisateur user;
                QJsonObject userObj = value.toObject();

                // Récupère les valeurs de chaque clé de l'objet JSON et les affecte aux attributs de l'objet utilisateur
                user.id = userObj["id"].toInt();
                user.isadmin = userObj["isadmin"].toBool();
                user.nom = userObj["nom"].toString();
                user.prenom = userObj["prenom"].toString();
                user.classe = userObj["classe"].toString();
                user.badge = userObj["badge"].toString();
                user.photo = userObj["photo"].toString();
                user.password = userObj["password"].toString();
                user.telephone = userObj["telephone"].toString();
                user.mail = userObj["mail"].toString();
                user.infos = userObj["infos"].toString();
                user.quota = userObj["quota"].toDouble();

                // Ajoute l'objet utilisateur à la liste
                userList.append(user);
            }
        }
    }
    qDebug() << userList;
    return userList;
}

QDebug operator<<(QDebug debug, const utilisateur& user)
{
    debug.nospace() << "utilisateur("
        << "id: " << user.id
        << ", isadmin: " << user.isadmin
        << ", nom: " << user.nom
        << ", prenom: " << user.prenom
        << ", classe: " << user.classe
        << ", badge: " << user.badge
        << ", photo: " << user.photo
        << ", password: " << user.password
        << ", telephone: " << user.telephone
        << ", mail: " << user.mail
        << ", infos: " << user.infos
        << ", quota: " << user.quota
        << ")";
    return debug;
}
