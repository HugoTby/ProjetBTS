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
	void insertUser(QString uid, QString prenom, QString nom, QString classe, QString tel, QString mail, QString password, QString infos, float quota);

private slots:
	void onFinishedRequest(QNetworkReply*);

signals:
	void onAPIReply(QNetworkReply*, QByteArray);
	void onAPIFailed(QNetworkReply*);
};

