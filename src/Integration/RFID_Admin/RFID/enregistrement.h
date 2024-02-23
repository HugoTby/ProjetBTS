#pragma once
#include <QSqlDatabase>
class enregistrement
{
private :
	char uid;
	char prenom;
	char nom;
	char classe;
	bool administrateur;
	char photo;
	char regime;
	char naissance;
	QSqlDatabase db;

public :

	void connectToDatabase(int hostname, int nameDatabase, int username, int password);
	void insertToDatabase(char uid, char prenom, char nom, char classe, bool administrateur, char photo, char regime, char naissance);

};

