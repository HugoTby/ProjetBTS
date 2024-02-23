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
    QString naissance;
    QSqlDatabase db;

public:
    enregistrement(); // Constructeur
    void connectToDatabase(QString hostname, QString nameDatabase, QString username, QString password);
    void insertToDatabase(QString uid, QString prenom, QString nom, QString classe, QString administrateur, QString photo, QString regime, QString naissance);
    QString selectUidFromDatabase(const QString& uid);
};
