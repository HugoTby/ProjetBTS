#pragma once
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery>


class callAPI : public QObject
{
	Q_OBJECT
private:
	QNetworkAccessManager manager;
public:
	callAPI(QObject* parent = nullptr);
	void selectWhereUID(QString uid);
	void checkTimeandQuota(QString uid);
private slots:
	void onFinishedRequest(QNetworkReply*);
	void GetInfosQuotaHeures(QNetworkReply*, QByteArray);

signals:
	void onAPIReply(QNetworkReply*, QByteArray);
	void onAPIFailed(QNetworkReply*);
	void onBoxDispoReceived(int boxDispo);
};

