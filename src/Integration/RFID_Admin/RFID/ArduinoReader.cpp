#include "ArduinoReader.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimer>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>

ArduinoReader::ArduinoReader(QObject* parent) : QObject(parent)
{
	serial = new QSerialPort(this);
	server = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);

	// Remplacez "COM3" par le port série de votre Arduino
	serial->setPortName("COM5");
	serial->setBaudRate(QSerialPort::Baud9600);

	connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
	connect(server, &QWebSocketServer::newConnection, this, &ArduinoReader::onNewConnection);

	qDebug() << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

	if (serial->open(QIODevice::ReadOnly)) {
		qDebug() << "SERIAL_PORT_OPENED_ON_COM_3.";

		if (server->listen(QHostAddress::Any, 12345)) { // Choisissez le port que vous préférez
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

	// Timer pour envoyer les données au client toutes les 100 millisecondes
	connect(&sendTimer, &QTimer::timeout, this, &ArduinoReader::sendToClients);
	sendTimer.start(100);

	// Initialiser la connexion à la base de données MySQL
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("192.168.64.200");
	db.setDatabaseName("RFID");
	db.setUserName("root");
	db.setPassword("root");

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

				// Récupérer les données associées à l'UID depuis la base de données
				QString jsonData = getDataFromDatabase(uid);

				// Envoyer les données au client WebSocket
				foreach(QWebSocket * client, clients) {
					client->sendTextMessage(jsonData);
				}
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

		// Envoyer l'UID aux clients WebSocket connectés
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

QString ArduinoReader::getDataFromDatabase(const QString& uid)
{
	// Exécuter la requête SQL pour récupérer les données associées à l'UID
	QSqlQuery query(db);
	query.prepare("SELECT * FROM utilisateurs WHERE uid = :uid");
	query.bindValue(":uid", uid);

	if (!query.exec()) {
		qDebug() << "ERROR_SQL_REQUEST :" << query.lastError().text();
		return QString();  // Retourner une chaîne vide en cas d'erreur
	}

	// Créer un objet JSON avec les résultats de la requête
	QJsonObject jsonData;

	if (query.next()) {
		jsonData["id"] = query.value(0).toInt();
		jsonData["uid"] = query.value(1).toString();
		jsonData["prenom"] = query.value(2).toString();
		jsonData["nom"] = query.value(3).toString();
		jsonData["classe"] = query.value(4).toString();
		jsonData["administrateur"] = query.value(5).toString();
		jsonData["photo"] = query.value(6).toString();
		jsonData["regime"] = query.value(7).toString();
		jsonData["naissance"] = query.value(8).toString();
	}

	// Convertir l'objet JSON en chaîne JSON
	QJsonDocument jsonDoc(jsonData);
	return jsonDoc.toJson(QJsonDocument::Compact);
}