#include <QtCore/QCoreApplication>
#include "Arduinoreader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ArduinoReader arduinoReader;
    return a.exec();
}
