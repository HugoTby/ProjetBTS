#include "APIReplyHandler.h"

APIReplyHandler::APIReplyHandler(QString pathToHandle)
{
	path = pathToHandle;
}

void APIReplyHandler::handleReply(QNetworkReply* reply, QByteArray responseData)
{
	QNetworkAccessManager::Operation operation = reply->operation();
	QString localPath = reply->url().path();

	if (localPath.startsWith(path))
	{
        switch (operation)
        {
        case QNetworkAccessManager::Operation::PostOperation:
            onPostReply(responseData);
            break;

        case QNetworkAccessManager::Operation::GetOperation:
            onGetReply(responseData);
            break;

        case QNetworkAccessManager::Operation::PutOperation:
            onPutReply(responseData);
            break;

        case QNetworkAccessManager::Operation::DeleteOperation:
            onDeleteReply(responseData);
            break;
        }
	}
}
