#include "enregistrement.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "ArduinoReader.h"
#include <QDebug>

enregistrement::enregistrement() {} // D�finition du constructeur par d�faut

void enregistrement::connectToDatabase(QString hostname, QString nameDatabase, QString username, QString password)
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostname);
    db.setDatabaseName(nameDatabase);
    db.setUserName(username);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "FAILED_TO_CONNECT_TO_DATABASE:" << db.lastError().text();
    }
    else {
        qDebug() << "DATABASE_CONNECTED.";
    }
}

void enregistrement::insertToDatabase(QString uid, QString prenom, QString nom, QString classe, QString administrateur, QString photo, QString regime, QString naissance)
{
    connectToDatabase("192.168.64.200", "RFID", "root", "root");

    QSqlQuery insert(db);
    insert.prepare("INSERT INTO `utilisateurs` (`uid`, `prenom`, `nom`, `classe`, `administrateur`, `photo`, `regime`, `naissance`) VALUES(:uid, :prenom, :nom, :classe, :administrateur, :photo, :regime, :naissance)");

    insert.bindValue(":uid", uid);
    insert.bindValue(":prenom", prenom);
    insert.bindValue(":nom", nom);
    insert.bindValue(":classe", classe);
    insert.bindValue(":administrateur", administrateur);
    insert.bindValue(":photo", photo);
    insert.bindValue(":regime", regime);
    insert.bindValue(":naissance", naissance);
    if (!insert.exec()) {
        qDebug() << "ERROR_INSERTING_TO_DATABASE:" << insert.lastError().text();
    }
    else {
        qDebug() << "DATA_INSERTED_TO_DATABASE.";
    }
}

QString enregistrement::selectUidFromDatabase(const QString& uid)
{
    if (!db.isOpen()) {
        qDebug() << "DATABASE_NOT_OPEN.";
        return QString();
    }

    QSqlQuery select(db);
    select.prepare("SELECT * FROM `utilisateurs` WHERE `uid` = :uid");
    select.bindValue(":uid", uid);
    if (!select.exec()) {
        qDebug() << "ERROR_SELECTING_FROM_DATABASE:" << select.lastError().text();
        return QString();
    }

    // Cr�er un objet JSON pour stocker les donn�es de l'UID s�lectionn�
    QJsonObject jsonObject;

    // V�rifier si un enregistrement a �t� trouv� avec cet UID
    if (select.next()) {
        jsonObject["id"] = select.value("id").toInt();
        jsonObject["uid"] = select.value("uid").toString();
        jsonObject["prenom"] = select.value("prenom").toString();
        jsonObject["nom"] = select.value("nom").toString();
        jsonObject["classe"] = select.value("classe").toString();
        jsonObject["administrateur"] = select.value("administrateur").toString();
        jsonObject["photo"] = select.value("photo").toString();
        jsonObject["regime"] = select.value("regime").toString();
        jsonObject["naissance"] = select.value("naissance").toString();
    }

    // Convertir l'objet JSON en une cha�ne JSON
    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Compact);
}