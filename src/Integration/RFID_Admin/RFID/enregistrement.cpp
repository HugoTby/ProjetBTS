#include "enregistrement.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

void enregistrement::connectToDatabase(int hostname, int nameDatabase, int username, int password)
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("192.168.64.200");
	db.setDatabaseName("RFID");
	db.setUserName("root");
	db.setPassword("root");

	if (!db.open()) {
		qDebug() << "FAILED_TO_CONNECT_TO_DATABASE.";
	}
}

void enregistrement::insertToDatabase(char uid, char prenom, char nom, char classe, bool administrateur, char photo, char regime, char naissance)
{
}
