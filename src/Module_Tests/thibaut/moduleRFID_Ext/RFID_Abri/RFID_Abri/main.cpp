#include <QtCore/QCoreApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test test;
    qDebug() << "caca1";
    test.envoiTrame();
    qDebug() << "caca2";
    return a.exec();
}
