#include <QtCore/QCoreApplication>
#include <QCoreApplication>
#include "callAPI.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    callAPI test;
    QString uid = "UID8556";
    QString prenom = "thibaut";
    QString nom = "tiennot";
    QString classe = "SN";
    QString tel = "0617457865";
    QString mail = "kijkjht@gmail.com";
    QString password = "fdshg";
    QString infos = NULL;
    float quota = 10;
    test.insertUser(uid, prenom, nom, classe, tel, mail, password, infos, quota);

    return a.exec();
}
