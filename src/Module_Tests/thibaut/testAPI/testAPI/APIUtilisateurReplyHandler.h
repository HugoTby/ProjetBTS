#pragma once
#include "APIReplyHandler.h"
class APIUtilisateurReplyHandler :
    public APIReplyHandler
{
public:
    APIUtilisateurReplyHandler();

	virtual void onGetReply(QByteArray);
	virtual void onPutReply(QByteArray);
	virtual void onPostReply(QByteArray);
	virtual void onDeleteReply(QByteArray);
};

