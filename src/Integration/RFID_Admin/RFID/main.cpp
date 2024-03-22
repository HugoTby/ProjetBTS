#include <QCoreApplication>
#include "Arduinoreader.h"
#include "enregistrement.h"
#include <QString>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ArduinoReader arduinoReader;
	//QString uid = "abcs";
	//QString prenom = "tibo";
	//QString nom = "tiennot";
	//QString classe = "sn2";
	//QString administrateur = "oui";
	//QString photo = "fgdsfdsujhfdshfdshjqfhdjfhd";
	//QString regime = "dp";
	//QString naissance = "03/10/2003";


	//enregistrement test;
	//
	//test.insertToDatabase(uid, prenom, nom, classe, administrateur, photo, regime, naissance);

	return a.exec();
}


