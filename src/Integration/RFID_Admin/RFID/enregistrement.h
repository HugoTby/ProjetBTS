#pragma once
#include <QSqlDatabase>

class enregistrement
{
private:
    QString uid;
    QString prenom;
    QString nom;
    QString classe;
    QString administrateur;
    QString photo;
    QString regime;
    QString infos;
    QString tel;
    QString mail;
    QString quota;
    QSqlDatabase db;

public:
    enregistrement(); // Constructeur
    void connectToDatabase(QString hostname, QString nameDatabase, QString username, QString password);
    void insertToDatabase(QString administrateur, QString nom, QString prenom, QString classe, QString uid, QString photo, QString password, QString tel, QString mail, QString infos, QString quota);
    QString selectUidFromDatabase(const QString& uid);
    QString formulaire();
};
