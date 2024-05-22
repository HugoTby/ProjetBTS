#pragma once
#include <qobject.h>
#include "callAPI.h"
#include "APIReplyHandler.h"

class TestAPI :
    public QObject
{
    callAPI api;

    QList<APIReplyHandler*> handlers;

private slots:
    void onAPIReply(QNetworkReply*, QByteArray);
    void onAPIFailed(QNetworkReply*);

public:
    void startTestsInsert();
    void startTestsGetInfos();
    void startTestsCheckTimeAndQuota();
    TestAPI(QObject * parent = nullptr);
};

