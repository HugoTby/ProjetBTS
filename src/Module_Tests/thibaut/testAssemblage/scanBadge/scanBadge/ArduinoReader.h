#pragma once
#include "callAPI.h"
#include "inscription.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimer>
#include <QDebug>

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
	void onBadgeScanned();
private:
	callAPI api;
	QSerialPort* serial;
	QWebSocketServer* server;
	QList<QWebSocket*> clients;
	QTimer sendTimer;
	QByteArray buffer;
	QString uid;
	int formShown;
};