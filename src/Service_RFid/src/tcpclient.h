#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class TCPClient : public QObject
{
    Q_OBJECT
public:
    TCPClient(QObject *parent = nullptr);
    ~TCPClient();

    void connectToHost(const QString &host, quint16 port);
    void sendData(const QByteArray &data);
    void closeConnection();

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray &data);

private slots:
    void onConnected();
    void onDisconnected();
    void onDataReceived();

private:
    QTcpSocket *m_socket;

};

#endif // TCPCLIENT_H
