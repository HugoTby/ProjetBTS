#pragma once
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery>
#include <QSerialPort>

class callAPI : public QObject
{
	Q_OBJECT
private:
	QNetworkAccessManager manager;
	QSerialPort* serial;
	QTimer* timer;
public:
	callAPI(QObject* parent = nullptr);
	~callAPI() {
		serial->close();
	}
	void selectWhereUID(QString uid);
	void checkTimeandQuota(QString uid);
	void verifyBoxUsedByUser(QString uid);
private slots:
	void onFinishedRequest(QNetworkReply*);
	void GetInfosQuotaHeures(QNetworkReply*, QByteArray);
	void allumerLed(int boxDispo);
signals:
	void onAPIReply(QNetworkReply*, QByteArray);
	void onAPIFailed(QNetworkReply*);
	void onBoxDispoReceived(int boxDispo);
};

