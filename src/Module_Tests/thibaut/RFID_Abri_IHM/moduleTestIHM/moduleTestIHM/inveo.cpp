#include "inveo.h"

inveo::inveo(QString readerIP, int port, QObject* parent)
    : QModbusTcpClient(readerIP, port, parent)
{

}

inveo::~inveo()
{
}

void inveo::connectToHost()
{
    QModbusTcpClient::connectToHost();
}

void inveo::deleteLater()
{
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
}

void inveo::receiveMultipleHoldingRegistersSentence(quint16 startAdress, QVector <quint16> values) {

}

void inveo::onConnected()
{
}

void inveo::onDisconnected()
{
}

void inveo::readDataSlot()
{
}


/*
void inveo::linkEstablished()
{
    emit emitAcceptSound();
    qDebug() << "signal etabli";
}

void inveo::linkLost()
{
    emit emitRejectSound();
    qDebug() << "signal perdu";
}
*/