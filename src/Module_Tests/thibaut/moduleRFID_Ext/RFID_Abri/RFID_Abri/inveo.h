#pragma once
#include "QModbusTcpClient.h"
#include <qtimer.h>
class inveo :
    public QModbusTcpClient
{
    Q_OBJECT
    QTimer* timer;
    const QString defaultData;
    QString lastDataString;

private:

public:
    inveo(QString readerIP, int port = 502, QObject* parent = nullptr);
    virtual ~inveo();
    virtual void connectToHost();
    void emitAcceptSound();
    void emitRejectSound();

private slots:
    void receiveMultipleHoldingRegistersSentence(quint16 startAdress, QVector <quint16> values);
    void onConnected();
    void onDisconnected();
    void readDataSlot();
signals:
    void cardScanned(QString cardData);
    void linkEstablished();
    void linkLost();
};

