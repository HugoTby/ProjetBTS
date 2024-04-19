#include "ArduinoReader.h"

ArduinoReader::ArduinoReader(QObject* parent) : QObject(parent)
{
	serial = new QSerialPort(this);
	server = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);
	// Remplacez "COMX" par le port s?rie de votre Arduino
	QString port = "COM6";
	serial->setPortName(port);
	serial->setBaudRate(QSerialPort::Baud9600);

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
