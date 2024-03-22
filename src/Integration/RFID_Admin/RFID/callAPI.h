#pragma once
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>

class callAPI : public QObject
{
	Q_OBJECT
private:
	QNetworkAccessManager manager;
public:
	callAPI(QObject* parent = nullptr);
	void selectWhereUID(QString uid);

private slots:
	void onFinishedRequest(QNetworkReply*);

signals:
	void onAPIReply(QNetworkReply*, QByteArray);
	void onAPIFailed(QNetworkReply*);
};

