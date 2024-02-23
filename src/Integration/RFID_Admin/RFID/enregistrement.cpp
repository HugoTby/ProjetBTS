#include "enregistrement.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

void enregistrement::connectToDatabase(QString hostname, QString nameDatabase, QString username, QString password)
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(hostname);
	db.setDatabaseName(nameDatabase);
	db.setUserName(username);
	db.setPassword(password);

	if (!db.open()) {
		qDebug() << "FAILED_TO_CONNECT_TO_DATABASE.";
	}
}

void enregistrement::insertToDatabase(QString uid, QString prenom, QString nom, QString classe, bool administrateur, QString photo, QString regime, QString naissance)
{
	connectToDatabase("192.168.64.200", "RFID", "root", "root");
	QSqlQuery insert(db);
	insert.prepare("INSERT INTO `utilisateurs`(`uid`, `prenom`, `nom`, `classe`, `administrateur`, `photo`, `regime`, `naissance`) VALUES (':uid',':prenom',':nom',':classe',':administrateur',':photo',':regime',':naissance')");
	insert.bindValue(":uid", uid);
	insert.bindValue(":prenom", prenom);
	insert.bindValue(":nom", nom);
	insert.bindValue(":classe", classe);
	insert.bindValue(":administrateur", administrateur);
	insert.bindValue(":photo", photo);
	insert.bindValue(":regime", regime);
	insert.bindValue(":naissance", naissance);

}
