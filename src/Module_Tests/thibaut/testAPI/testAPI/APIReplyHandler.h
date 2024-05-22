#pragma once

#include <qstring.h>
#include <qnetworkreply.h>

class APIReplyHandler
{
private:
	QString path;

public:
	APIReplyHandler(QString pathToHandle);
	void handleReply(QNetworkReply* reply, QByteArray responseData);
	virtual void onGetReply(QByteArray) = 0;
	virtual void onPutReply(QByteArray) = 0;
	virtual void onPostReply(QByteArray) = 0;
	virtual void onDeleteReply(QByteArray) = 0;
};

