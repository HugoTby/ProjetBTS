#pragma once
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
#include <QNetworkReply>
#include "callAPI.h"

class ArduinoReader : public QObject
{
	Q_OBJECT

public:
	ArduinoReader(QObject* parent = nullptr);
public slots:
	void readData();
	void sendToClients();
	void onNewConnection();
	void onSocketDisconnected();
	void onAPIReplyReceived(QNetworkReply*, QByteArray);
	void onAPIFailed(QNetworkReply*);

private:
	callAPI api;
	QSerialPort* serial;
	QWebSocketServer* server;
	QList<QWebSocket*> clients;
	QTimer sendTimer;
	QByteArray buffer;
	QSqlDatabase db;
	QString getDataFromDatabase(const QString& uid);
	void handleResponse(const QByteArray& data);
};