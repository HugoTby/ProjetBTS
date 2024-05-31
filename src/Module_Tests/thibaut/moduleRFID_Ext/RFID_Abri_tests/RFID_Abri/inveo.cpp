#include "inveo.h"
#define DEFAULT_DATA "00000000000000"

inveo::inveo(QString readerIP, int port, QObject* parent)
    : QModbusTcpClient(readerIP, port, parent), defaultData(DEFAULT_DATA)
{
    connect(this, &inveo::linkEstablished, this, &inveo::onConnected);
    connect(this, &QModbusTcpClient::onReadMultipleHoldingRegistersSentence, this, &inveo::receiveMultipleHoldingRegistersSentence);
    connect(this, &inveo::linkLost, this, &inveo::onDisconnected);

    // Create a QTimer that triggers every second
    timer = new QTimer(this);
    timer->setInterval(1000);

    // Connect the timeout() signal of the QTimer to the readDataSlot() slot of the inveo object
    connect(timer, &QTimer::timeout, this, &inveo::readDataSlot);

    // Start the QTimer
    timer->start();
}


inveo::~inveo()
{
    deleteLater();
    emit linkLost();
}

void inveo::connectToHost()
{
    QModbusTcpClient::connectToHost();
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
    // Vérifier que la connexion est établie
    if (state() == QTcpSocket::ConnectedState)
    {
        // Envoyer la requête Modbus
        forceSingleCoilFC5(14, true);
    }
}

void inveo::emitRejectSound()
{
    // Vérifier que la connexion est établie
    if (state() == QTcpSocket::ConnectedState)
    {
        // Envoyer la requête Modbus
        forceSingleCoilFC5(15, true);
    }
}

void inveo::receiveMultipleHoldingRegistersSentence(quint16 startAddress, QVector<quint16> values)
{
    qDebug() << values;
}

void inveo::onConnected()
{
    emitAcceptSound();
}

void inveo::onDisconnected()
{
    emitRejectSound();
    timer->stop();
}

void inveo::readDataSlot()
{
    if (state() == QTcpSocket::ConnectedState)
    {
        quint16 startAddress = 1; 
        quint16 nbWord = 24; 
        QModbusTcpClient::readMultipleHoldingRegistersFC3(startAddress, nbWord);
        //receiveMultipleHoldingRegistersSentence(startAddress);
        //emit cardScanned;
        //emitAcceptSound();
        //qDebug() << "ecoute du lecteur";
    }
}