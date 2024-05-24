#include "test.h"

test::test()
    : QObject(nullptr)
{
    QString readerIP = "192.168.65.240";
    int port = 502;
    o = new inveo(readerIP, port, this);
    o->connectToHost();
    // Connecter le slot onConnected à la méthode emitAcceptSound
    QObject::connect(o, &QTcpSocket::connected, this, &test::envoiTrame);
}

void test::envoiTrame()
{
    o->emitAcceptSound();

    
}