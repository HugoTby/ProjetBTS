#pragma once
#include <QSqlDatabase>
class enregistrement
{
private :
	QString uid;
	QString prenom;
	QString nom;
	QString classe;
	bool administrateur;
	QString photo;
	QString regime;
	QString naissance;
	QSqlDatabase db;

public :

	void connectToDatabase(QString hostname, QString nameDatabase, QString username, QString password);
	void insertToDatabase(QString uid, QString prenom, QString nom, QString classe, bool administrateur, QString photo, QString regime, QString naissance);

};

