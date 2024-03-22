#include "enregistrement.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "ArduinoReader.h"
#include <QDebug>
#include <iostream>
#include <string>

enregistrement::enregistrement() {} // Définition du constructeur par défaut

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

void enregistrement::insertToDatabase(QString administrateur, QString nom, QString prenom, QString classe, QString uid, QString photo, QString password, QString tel, QString mail, QString infos, QString quota)
{
    connectToDatabase("192.168.65.105", "sandbox_projet_bts", "admin", "a915g5GQ");

    QSqlQuery insert(db);
    insert.prepare("INSERT INTO `utilisateur`(`isadmin_utilisateur`, `nom_utilisateur`, `prenom_utilisateur`, `classe_utilisateur`, `badge_utilisateur`, `photo_utilisateur`, `password_utilisateur`, `telephone_utilisateur`, `mail_utilisateur`, `infos_utilisateur`, `quota_utilisateur`) VALUES(:administrateur, :nom, :prenom, :classe, :uid, :photo, :password, :tel, :mail, :infos, :quota)");

    insert.bindValue(":uid", uid);
    insert.bindValue(":prenom", prenom);
    insert.bindValue(":nom", nom);
    insert.bindValue(":classe", classe);
    insert.bindValue(":administrateur", administrateur);
    insert.bindValue(":photo", photo);
    insert.bindValue(":password", password); // Ajoutez cette ligne si vous voulez insérer un mot de passe
    insert.bindValue(":tel", tel);
    insert.bindValue(":mail", mail);
    insert.bindValue(":infos", infos);
    insert.bindValue(":quota", quota);

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
    select.prepare("SELECT * FROM utilisateur WHERE badge_utilisateur = :uid");
    select.bindValue(":uid", uid);
    if (!select.exec()) {
        qDebug() << "ERROR_SELECTING_FROM_DATABASE:" << select.lastError().text();
        return QString();
    }

    // Créer un objet JSON pour stocker les données de l'UID sélectionné
    QJsonObject jsonObject;

    // Vérifier si un enregistrement a été trouvé avec cet UID
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

    // Convertir l'objet JSON en une chaîne JSON
    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

QString enregistrement::formulaire()
{
    QJsonObject jsonData;

    std::string prenom_str, nom_str, classe_str, tel_str, mail_str, infos_str, quota_str, password_str;
    std::cout << "Saisir prenom : ";
    std::cin >> prenom_str;
    std::cout << "Saisir nom : ";
    std::cin >> nom_str;
    std::cout << "Saisir classe : ";
    std::cin >> classe_str;
    std::cout << "Saisir tel : ";
    std::cin >> tel_str;
    std::cout << "Saisir mail : ";
    std::cin >> mail_str;
    std::cout << "Saisir password : ";
    std::cin >> password_str;
    std::cout << "Saisir infos : ";
    std::cin >> infos_str;
    std::cout << "Saisir quota : ";
    std::cin >> quota_str;

    QString prenom = QString::fromStdString(prenom_str);
    QString nom = QString::fromStdString(nom_str);
    QString classe = QString::fromStdString(classe_str);
    QString tel = QString::fromStdString(tel_str);
    QString mail = QString::fromStdString(mail_str);
    QString password = QString::fromStdString(password_str);
    QString infos = QString::fromStdString(infos_str);
    QString quota = QString::fromStdString(quota_str);

    // Insérer un nouvel utilisateur avec les données saisies
    enregistrement reg;
    reg.insertToDatabase("0", nom, prenom, classe, uid, "photo.jpg", password, tel, mail, infos, quota);

    // Mettre à jour l'objet JSON avec les données du nouvel utilisateur
    jsonData["id"] = -1;  // L'ID sera défini par la base de données, nous utilisons -1 comme valeur temporaire
    jsonData["uid"] = uid;
    jsonData["administrateur"] = "0";
    jsonData["prenom"] = prenom;
    jsonData["nom"] = nom;
    jsonData["classe"] = classe;
    jsonData["photo"] = "photo.jpg";
    jsonData["tel"] = tel;
    jsonData["mail"] = mail;
    jsonData["password"] = password;
    jsonData["infos"] = infos;
    //jsonData["regime"] = regime;
    jsonData["quota"] = quota;

    	QJsonDocument jsonDoc(jsonData);
	return jsonDoc.toJson(QJsonDocument::Compact);

}
