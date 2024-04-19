#include "ArduinoReader.h"

ArduinoReader::ArduinoReader(QObject* parent) : QObject(parent)
{
	serial = new QSerialPort(this);
	server = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);
	// Remplacez "COMX" par le port série de votre Arduino
	QString port = "COM6";
	serial->setPortName(port);
	serial->setBaudRate(QSerialPort::Baud9600);

	connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
	connect(server, &QWebSocketServer::newConnection, this, &ArduinoReader::onNewConnection);

	qDebug() << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

	if (serial->open(QIODevice::ReadOnly)) {
		qDebug() << "SERIAL_PORT_OPENED_ON : " + port;

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

	// Drapeau pour vérifier si le formulaire a déjà été affiché
	formShown = false;
}

QString ArduinoReader::getUid()
{
	return this->uid;
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
			this->uid = uid; // pas sûr que ca marche

			if (!uid.isEmpty()) {
				qDebug() << uid;
				//affichage du formulaire
				onBadgeScanned();
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

void ArduinoReader::onBadgeScanned()
{
	// Vérifier si le formulaire a déjà été affiché
	if (!formShown) {
		// Afficher le formulaire d'inscription
		inscription inscription;
		QStringList infos = inscription.formUser();

		// Afficher les informations de la liste
		//qInfo << "Voici les données saisies :";
		for (int i = 0; i < infos.size(); i++) {
			qDebug() << "Info" << i + 1 << ":" << infos[i];
		}

		// Définir le drapeau pour indiquer que le formulaire a été affiché
		formShown = true;
		QString prenom = QString::fromStdString(infos[0].toStdString());
		QString nom = QString::fromStdString(infos[1].toStdString());
		QString classe = QString::fromStdString(infos[2].toStdString());
		QString tel = QString::fromStdString(infos[3].toStdString());
		QString mail = QString::fromStdString(infos[4].toStdString());
		QString password = QString::fromStdString(infos[5].toStdString());
		QString infosStr = QString::fromStdString(infos[6].toStdString());
		float quota = std::stof(infos[7].toStdString());


		// Appeler l'API pour insérer l'utilisateur dans la base de données
		QString uid = getUid();
		qDebug() << "test affichage" + uid;
		api.selectWhereUID(uid);
		//vérifier pour que si le QJsonObject est vide, alors on insertUser, sinon on affiche user déjà inscrit
		// le QJsonObject est affiché dans callAPI.cpp, ici : QObject::connect(&manager, &QNetworkAccessManager::finished, this, &callAPI::onFinishedRequest);
		api.insertUser(uid, prenom, nom, classe, tel, mail, password, infosStr, quota);
	}

}
