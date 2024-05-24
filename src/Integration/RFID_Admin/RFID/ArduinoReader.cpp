#include "ArduinoReader.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimer>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "enregistrement.h"
#include <iostream>
#include <string>
#include "utilisateur.h"


ArduinoReader::ArduinoReader(QObject* parent) : QObject(parent)
{
	serial = new QSerialPort(this);
	server = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);
	// Remplacez "COMX" par le port s?rie de votre Arduino
	QString port = "COM1";
	serial->setPortName(port);
	serial->setBaudRate(QSerialPort::Baud9600);

	connect(&api, & callAPI::onAPIReply, this, & ArduinoReader::onAPIReplyReceived);
	//connect(&api, &callAPI::onAPIReply, this, &ArduinoReader::onAPIReplyReceived);
	connect(&api, &callAPI::onAPIFailed, this, &ArduinoReader::onAPIFailed);

	connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
	connect(server, &QWebSocketServer::newConnection, this, &ArduinoReader::onNewConnection);

	qDebug() << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

	if (serial->open(QIODevice::ReadOnly)) {
		qDebug() << "SERIAL_PORT_OPENED_ON : " + port;

		if (server->listen(QHostAddress::Any, 12345)) { // Choisissez le port que vous pr?f?rez
			qDebug() << "WEBSOCKET_SERVER_OPENED_ON" << server->serverPort() << ".";
		}
		else {
			qDebug() << "FAILED_TO_OPEN_WEBSOCKET_SERVER.";
		}
	}
	else {
		qDebug() << "----- FAILED_TO_OPEN_SERIAL_PORT. -----\n\nPlease check the Arduino connection\nand the COM port entered in the code.";
	}

	qDebug() << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

	// Timer pour envoyer les donn?es au client toutes les 100 millisecondes
	connect(&sendTimer, &QTimer::timeout, this, &ArduinoReader::sendToClients);
	sendTimer.start(100);

	// Initialiser la connexion ? la base de donn?es MySQL
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("192.168.65.105");
	db.setDatabaseName("sandbox_projet_bts");
	db.setUserName("admin");
	db.setPassword("a915g5GQ");

	if (!db.open()) {
		qDebug() << "FAILED_TO_CONNECT_TO_DATABASE.";
	}
}

void ArduinoReader::readData()
{
	QByteArray data = serial->readAll();
	if (!data.isEmpty()) {
		buffer.append(data);

		while (buffer.contains("\r\n")) {
			int endIndex = buffer.indexOf("\r\n") + 2;
			QByteArray uidData = buffer.left(endIndex);
			buffer = buffer.mid(endIndex);

			QString uid = QString(uidData).remove(QRegExp("[^A-Fa-f0-9]"));

			if (!uid.isEmpty()) {
				qDebug() << uid;

				// R?cup?rer les donn?es associ?es ? l'UID depuis la base de donn?es
				api.selectWhereUID(uid);
			}
		}
	}
}

void ArduinoReader::sendToClients()
{
	while (buffer.size() >= 3) {  // Taille minimale d'un UID dans cet exemple
		QByteArray uidData = buffer.left(3);
		buffer = buffer.mid(3);

		QString uid = QString(uidData).remove(QRegExp("[^A-Fa-f0-9]"));
		qDebug() << uid;

		// Envoyer l'UID aux clients WebSocket connect?s
		foreach(QWebSocket * client, clients) {
			client->sendTextMessage(uid);
		}
	}
}

void ArduinoReader::onNewConnection()
{
	QWebSocket* clientSocket = server->nextPendingConnection();
	connect(clientSocket, &QWebSocket::disconnected, this, &ArduinoReader::onSocketDisconnected);
	clients << clientSocket;
	qDebug() << "NEW_WEBSOCKET_CONNECTION.";
}

void ArduinoReader::onSocketDisconnected()
{
	QWebSocket* clientSocket = qobject_cast<QWebSocket*>(sender());
	if (clientSocket) {
		clients.removeOne(clientSocket);
		clientSocket->deleteLater();
		qDebug() << "WEBSOCKET_CONNECTION_CLOSED.";
	}
}

void ArduinoReader::onAPIReplyReceived(QNetworkReply* reply, QByteArray jsonData)
{
	qDebug() << "Response:" << jsonData;
	utilisateur user1;
	user1.toUncypherJSON(jsonData);

	if (jsonData == "[]")
	{
		qDebug() << "Pas inscrit dans le systeme";
		//user1.formUser();
		
	}
	else
	{
		qDebug() << "Utilisateur trouvé";
	}


	// Envoyer les donn?es au client WebSocket
	foreach(QWebSocket * client, clients) {
		client->sendTextMessage(jsonData);
	}
}

void ArduinoReader::onAPIFailed(QNetworkReply*)
{
	qDebug() << "API call failed";
}

void handleResponse(const QByteArray& data)
{
	qDebug() << "Response received:" << data;
}
