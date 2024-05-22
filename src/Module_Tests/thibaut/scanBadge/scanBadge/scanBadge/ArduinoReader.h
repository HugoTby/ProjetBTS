#pragma once
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QTimer>

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
private:
	QSerialPort* serial;
	QWebSocketServer* server;
	QList<QWebSocket*> clients;
	QTimer sendTimer;
	QByteArray buffer;
};