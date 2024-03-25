#include "utilisateur.h"

QMap<QString, QVariant> utilisateur::toUncypherJSON(const QByteArray& jsonData)
{
    QMap<QString, QVariant> userMap;

    // Parse la r�ponse JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    // V�rifie si le parsing a r�ussi et si la r�ponse contient un tableau
    if (!jsonDoc.isNull() && jsonDoc.isArray()) {
        // R�cup�re le premier �l�ment du tableau (on suppose qu'il n'y a qu'un seul utilisateur)
        QJsonObject userObj = jsonDoc.array().at(0).toObject();

        // Parcourt les cl�s et les valeurs de l'objet JSON et les ajoute � la map
        for (QJsonObject::const_iterator it = userObj.constBegin(); it != userObj.constEnd(); ++it) {
            userMap.insert(it.key(), it.value().toVariant());
        }
    }

    return userMap;
}