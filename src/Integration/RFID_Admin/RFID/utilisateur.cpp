#include "utilisateur.h"

QMap<QString, QVariant> utilisateur::toUncypherJSON(const QByteArray& jsonData)
{
    QMap<QString, QVariant> userMap;

    // Parse la réponse JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    // Vérifie si le parsing a réussi et si la réponse contient un tableau
    if (!jsonDoc.isNull() && jsonDoc.isArray()) {
        // Récupère le premier élément du tableau (on suppose qu'il n'y a qu'un seul utilisateur)
        QJsonObject userObj = jsonDoc.array().at(0).toObject();

        // Parcourt les clés et les valeurs de l'objet JSON et les ajoute à la map
        for (QJsonObject::const_iterator it = userObj.constBegin(); it != userObj.constEnd(); ++it) {
            userMap.insert(it.key(), it.value().toVariant());
        }
    }

    return userMap;
}