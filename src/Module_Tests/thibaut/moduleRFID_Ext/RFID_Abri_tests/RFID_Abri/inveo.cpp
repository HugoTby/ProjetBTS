#include "inveo.h"

inveo::inveo(QString readerIP, int port, QObject* parent)
    : QModbusTcpClient(readerIP, port, parent) 
{

    QObject::connect(this, &inveo::linkEstablished, this, &inveo::onConnected);
    QObject::connect(this, &inveo::linkLost, this, &inveo::onDisconnected);

    // Cr�er un QTimer qui se d�clenche toutes les secondes
    timer = new QTimer(this);
    timer->setInterval(1000);

    // Connecter le signal timeout() du QTimer au slot readDataSlot() de la classe inveo
    QObject::connect(timer, &QTimer::timeout, this, &inveo::readDataSlot);

    // D�marrer le QTimer
    timer->start();
    //connect(this, &QModbusTcpClient::connected, this, &inveo::onConnected); //faire tourner le timer d'�coute toutes les secondes
}

inveo::~inveo()
{
    deleteLater();
    emit linkLost();
}

void inveo::connectToHost()
{
    QModbusTcpClient::connectToHost();
    timer->setInterval(1000);
    timer->start();
    if (QTcpSocket::ConnectedState) {
        emit linkEstablished();
    }
}

void inveo::deleteLater()
{
    QModbusTcpClient::deleteLater();
}


void inveo::emitAcceptSound()
{
    // V�rifier que la connexion est �tablie
    if (state() == QTcpSocket::ConnectedState)
    {
        // Envoyer la requ�te Modbus
        forceSingleCoilFC5(14, true);
    }
}

void inveo::emitRejectSound()
{
    // V�rifier que la connexion est �tablie
    if (state() == QTcpSocket::ConnectedState)
    {
        // Envoyer la requ�te Modbus
        forceSingleCoilFC5(15, true);
    }
}

void inveo::receiveMultipleHoldingRegistersSentence(quint16 startAddress, QVector<quint16> values)
{
}

void inveo::onConnected()
{
    emitAcceptSound();
    QModbusTcpClient::onDataRecv();
}

void inveo::onDisconnected()
{
    emitRejectSound();
}

void inveo::readDataSlot()
{
    if (state() == QTcpSocket::ConnectedState)
    {
        quint16 startAddress = 1; 
        quint16 nbWord = 24; 
        QModbusTcpClient::readMultipleHoldingRegistersFC3(startAddress, nbWord);
        qDebug() << "ecoute du lecteur";
    }
}