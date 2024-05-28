#include "inveo.h"

inveo::inveo(QString readerIP, int port, QObject* parent)
    : QModbusTcpClient(readerIP, port , parent)
{
    connect(this, &QModbusTcpClient::connected, this, &inveo::onConnected); //faire tourner le timer d'�coute toutes les secondes
    //connect(this, &inveo::cardScanned, this, &inveo::readDataSlot);
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
    QString cardData;

    // V�rifier que les donn�es re�ues ont la bonne taille
    if (values.size() >= 4)
    {
        // Extraire les donn�es de la carte RFID � partir des registres Modbus
        quint16 data1 = values[0];
        quint16 data2 = values[1];
        quint16 data3 = values[2];
        quint16 data4 = values[3];

        // Convertir les donn�es en une cha�ne de caract�res hexad�cimale
        cardData = QString("%1%2%3%4").arg(data1, 4, 16, QLatin1Char('0')).arg(data2, 4, 16, QLatin1Char('0')).arg(data3, 4, 16, QLatin1Char('0')).arg(data4, 4, 16, QLatin1Char('0'));
    }

    // �mettre le signal cardScanned avec les donn�es de la carte RFID
    qDebug() << "Carte scann�e : " << cardData;

    emit cardScanned(cardData);
}



void inveo::onConnected()
{
    // Cr�er un QTimer qui se d�clenche toutes les secondes
    QTimer* timer = new QTimer(this);
    timer->setInterval(1000);

    // Connecter le signal timeout() du QTimer au slot readDataSlot() de la classe inveo
    QObject::connect(timer, &QTimer::timeout, this, &inveo::readDataSlot);

    // D�marrer le QTimer
    timer->start();
}


void inveo::onDisconnected()
{
}

void inveo::readDataSlot()
{
    // V�rifier que la connexion est �tablie
    if (state() == QTcpSocket::ConnectedState)
    {
        // Envoyer la requ�te Modbus pour lire les donn�es de la carte RFID
        quint16 startAddress = 1; // Adresse de d�part du premier registre de maintien � lire
        quint16 nbWord = 4; // Nombre de registres de maintien � lire (une carte RFID Mifare contient 4 blocs de 16 octets)
        QModbusTcpClient::readMultipleHoldingRegistersFC3(startAddress, nbWord);
    }
}
