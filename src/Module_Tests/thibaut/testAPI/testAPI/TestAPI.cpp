#include "TestAPI.h"
#include "APIUtilisateurReplyHandler.h"

void TestAPI::onAPIReply(QNetworkReply* reply, QByteArray responseData)
{
    for (auto it = handlers.begin(); it != handlers.end(); it++)
    {
        (*it)->handleReply(reply, responseData);
    }
}


void TestAPI::onAPIFailed(QNetworkReply* reply)
{
}

void TestAPI::startTestsInsert()
{
    qInfo() << "Test /utilisateurs";
    QString uid = "EQJ255654";
    QString prenom = "thibaut";
    QString nom = "tiennot";
    QString classe = "SN2";
    QString tel = "0617830137";
    QString mail = "thibaut.tiennot@gmail.com";
    QString password = "qsdjnk12nml!:";
    QString infos = NULL;
    float quota = 10;
	api.insertUser(uid, prenom, nom, classe, tel, mail, password, infos, quota);
}

void TestAPI::startTestsGetInfos()
{
    
    qInfo() << "Test /utilisateurs/badge_utilisateur";
    QString uid = "ABCDEZ";
    api.selectWhereUID(uid);
    
    }

void TestAPI::startTestsCheckTimeAndQuota()
{
    qInfo() << "Test /utilisateurs/quota-depot/:uid";
    QString uid = "ABCDEZ";
    api.checkTimeandQuota(uid);
}

TestAPI::TestAPI(QObject* parent)
    : QObject(parent)
{
    handlers.push_back(new APIUtilisateurReplyHandler());

    QObject::connect(&api, &callAPI::onAPIReply, this, &TestAPI::onAPIReply);
    QObject::connect(&api, &callAPI::onAPIFailed, this, &TestAPI::onAPIFailed);
}
