#include <QtCore/QCoreApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    test test;
    return a.exec();
}
