#include "inveo.h"
#define DEFAULT_DATA "00000000"

inveo::inveo(QString readerIP, int port, QObject* parent)
    : QModbusTcpClient(readerIP, port, parent), defaultData(DEFAULT_DATA), lastDataString(DEFAULT_DATA)
{
    connect(this, &inveo::linkEstablished, this, &inveo::onConnected);
    connect(this, &QModbusTcpClient::onReadMultipleHoldingRegistersSentence, this, &inveo::receiveMultipleHoldingRegistersSentence);
    connect(this, &inveo::linkLost, this, &inveo::onDisconnected);
    connect(this, &inveo::cardScanned, this, &inveo::traitementInfos);
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
    // Extraire les valeurs de l'UID de la carte
    quint16 uid1 = values[4];
    quint16 uid2 = values[5];
    quint16 uid3 = values[6];
    quint16 uid4 = values[7];

    // Convertir les valeurs en hexadécimal
    QString uidHex1 = QString::asprintf("%02X", uid1);
    QString uidHex2 = QString::asprintf("%02X", uid2);
    QString uidHex3 = QString::asprintf("%02X", uid3);
    QString uidHex4 = QString::asprintf("%02X", uid4);
    QString uidHex = uidHex1 + uidHex2 + uidHex3 + uidHex4;
    if (uidHex != defaultData && uidHex != lastDataString) {
        emit cardScanned(uidHex);
        qDebug() << "nouvelle carte scannée";
        qDebug() << "UID :" << uidHex;
        lastDataString = uidHex;
    }
    else if (uidHex == defaultData) {
        lastDataString = "";
        qDebug() << "aucune carte scannée";
    }
    else if(uidHex == lastDataString){
        qDebug() << "meme carte scannée";
    }
}



void inveo::onConnected()
{
    emitAcceptSound();
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &inveo::readDataSlot);
    timer->start();
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
    }
}

void inveo::traitementInfos(QString cardData)
{
    api.checkTimeandQuota(cardData);
    emit &callAPI::onAPIReply;
}