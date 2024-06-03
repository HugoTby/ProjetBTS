#pragma once
#include "QModbusTcpClient.h"
#include <qtimer.h>
#include <QModbusDataUnit>
#include <QModbusReply>
#include "callAPI.h"

class inveo :
    public QModbusTcpClient
{
    Q_OBJECT
    QTimer* timer;
    const QString defaultData;
    QString lastDataString;
    callAPI api;
public:
    inveo(QString readerIP, int port = 502, QObject* parent = nullptr);
    virtual ~inveo();
    virtual void connectToHost();
    virtual void deleteLater();
    void emitAcceptSound();
    void emitRejectSound();
private slots:
    void receiveMultipleHoldingRegistersSentence(quint16 startAddress, QVector<quint16> values);
    void onConnected();
    void onDisconnected();
    void readDataSlot();
    void traitementInfos(QString cardData);
signals:
    void linkEstablished();
    void linkLost();
    void cardScanned(QString cardData);
};

