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
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "enregistrement.h"
#include <iostream>
#include <string>


ArduinoReader::ArduinoReader(QObject* parent) : QObject(parent)
{
	serial = new QSerialPort(this);
	server = new QWebSocketServer("WebSocket Server", QWebSocketServer::NonSecureMode, this);

	// Remplacez "COM3" par le port s?rie de votre Arduino
	serial->setPortName("COM5");
	serial->setBaudRate(QSerialPort::Baud9600);

	connect(&api, & callAPI::onAPIReply, this, & ArduinoReader::onAPIReplyReceived);
	connect(&api, &callAPI::onAPIFailed, this, &ArduinoReader::onAPIFailed);

	connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
	connect(server, &QWebSocketServer::newConnection, this, &ArduinoReader::onNewConnection);

	qDebug() << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

	if (serial->open(QIODevice::ReadOnly)) {
		qDebug() << "SERIAL_PORT_OPENED_ON_COM_3.";

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



	if (jsonData == "[]")
	{
		qDebug() << "Pas inscrit dans le systeme";
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



QString ArduinoReader::getDataFromDatabase(const QString& uid)
{
	// Exécuter la requête SQL pour récupérer les données associées à l'UID
	QSqlQuery query(db);
	query.prepare("SELECT * FROM utilisateur WHERE badge_utilisateur = :uid");
	query.bindValue(":uid", uid);

	if (!query.exec()) {
		qDebug() << "ERROR_SQL_REQUEST :" << query.lastError().text();
		return QString();  // Retourner une chaîne vide en cas d'erreur
	}

	// Créer un objet JSON avec les résultats de la requête
	QJsonObject jsonData;

	if (query.next()) {
		// Si un utilisateur est trouvé, remplir l'objet JSON avec ses données
		jsonData["id"] = query.value(0).toInt();
		jsonData["administrateur"] = query.value(1).toString();
		jsonData["nom"] = query.value(2).toString();
		jsonData["prenom"] = query.value(3).toString();
		jsonData["classe"] = query.value(4).toString();
		jsonData["uid"] = query.value(5).toString();
		jsonData["photo"] = query.value(6).toString();
		jsonData["tel"] = query.value(8).toString();
		jsonData["mail"] = query.value(9).toString();
		jsonData["infos"] = query.value(10).toString();
		jsonData["quota"] = query.value(11).toString();
	}
	else {
		// Si aucun utilisateur n'est trouvé, demander les informations manquantes à l'utilisateur
		std::string prenom_str, nom_str, classe_str, tel_str, mail_str, infos_str, quota_str, password_str;
		std::cout << "Saisir prenom : ";
		std::cin >> prenom_str;
		std::cout << "Saisir nom : ";
		std::cin >> nom_str;
		std::cout << "Saisir classe : ";
		std::cin >> classe_str;
		std::cout << "Saisir tel : ";
		std::cin >> tel_str;
		std::cout << "Saisir mail : ";
		std::cin >> mail_str;
		std::cout << "Saisir password : ";
		std::cin >> password_str;
		std::cout << "Saisir infos : ";
		std::cin >> infos_str;
		std::cout << "Saisir quota : ";
		std::cin >> quota_str;

		QString prenom = QString::fromStdString(prenom_str);
		QString nom = QString::fromStdString(nom_str);
		QString classe = QString::fromStdString(classe_str);
		QString tel = QString::fromStdString(tel_str);
		QString mail = QString::fromStdString(mail_str);
		QString password = QString::fromStdString(password_str);
		QString infos = QString::fromStdString(infos_str);
		QString quota = QString::fromStdString(quota_str);

		// Insérer un nouvel utilisateur avec les données saisies
		enregistrement reg;
		reg.insertToDatabase("0", nom, prenom, classe, uid, "photo.jpg", password, tel, mail, infos, quota);

		// Mettre à jour l'objet JSON avec les données du nouvel utilisateur
		jsonData["id"] = -1;  // L'ID sera défini par la base de données, nous utilisons -1 comme valeur temporaire
		jsonData["uid"] = uid;
		jsonData["administrateur"] = "0";
		jsonData["prenom"] = prenom;
		jsonData["nom"] = nom;
		jsonData["classe"] = classe;
		jsonData["photo"] = "photo.jpg";
		jsonData["tel"] = tel;
		jsonData["mail"] = mail;
		jsonData["password"] = password;
		jsonData["infos"] = infos;
		jsonData["quota"] = quota;
	}

	// Convertir l'objet JSON en chaîne JSON
	QJsonDocument jsonDoc(jsonData);
	return jsonDoc.toJson(QJsonDocument::Compact);
}