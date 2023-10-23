#ifndef MICROSERVICERFID_H
#define MICROSERVICERFID_H

#include <QObject>
#include "message.h"
#include "tcpclient.h"
#include "tcpcontroller.h"
#include "rfid.h"
#include <QTimer>

class MicroServiceRFID : public QObject
{
    Q_OBJECT
public:
    explicit MicroServiceRFID(QObject *parent = nullptr);

public slots:
        void frecuenciaConfig();
        void reConexion();
        void sendMsg();
        void processMsg(const QByteArray &data);
        void updatePressViaje(bool pressViajeRFID);
signals:

private:
    QRemoteObjectHost srcNode;
    RFID rfid;
    Message *msg=nullptr;
    TCPController controller;
    QTimer fre;
    bool pressViaje;
};

#endif // MICROSERVICERFID_H
