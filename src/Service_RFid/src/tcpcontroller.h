#ifndef TCPCONTROLLER_H
#define TCPCONTROLLER_H

#include <QObject>
#include "tcpclient.h"
#include <QByteArray>

class Message;

class TCPController : public QObject
{
    Q_OBJECT
public:
    TCPController(QObject *parent = nullptr);
    ~TCPController();

    void connectToHost(const QString &host, quint16 port);
    void sendData(const QByteArray &data);
    void sendMessage(Message *msg);
    void closeConnection();
    unsigned short calcCrc(unsigned char message[], int length);

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray &data);
private:
    TCPClient *m_client;

};

#endif // TCPCONTROLLER_H
