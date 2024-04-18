#include <QCoreApplication>
#include "callAPI.h"
#include "Arduinoreader.h"
#include "utilisateur.h"
#include <QDebug>



int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ArduinoReader arduinoReader;

    callAPI api;

    //utilisateur user;

    // Connecter le signal responseReceived au slot handleResponse
    //QObject::connect(&user, &utilisateur::responseReceived, &handleResponse);

    //api.selectWhereUID("ABCDEZ");

    return a.exec();
}


