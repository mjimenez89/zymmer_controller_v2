#include "tcpclient.h"

TCPClient::TCPClient(QObject *parent)
    : QObject{parent}
{
    m_socket = new QTcpSocket(this);

       connect(m_socket, &QTcpSocket::connected, this, &TCPClient::onConnected);
       connect(m_socket, &QTcpSocket::disconnected, this, &TCPClient::onDisconnected);
       connect(m_socket, &QTcpSocket::readyRead, this, &TCPClient::onDataReceived);


}

TCPClient::~TCPClient()
{
    closeConnection();
}

void TCPClient::connectToHost(const QString &host, quint16 port)
{
    m_socket->connectToHost(host, port);

}

void TCPClient::sendData(const QByteArray &data)
{

    m_socket->write(data);

}

void TCPClient::closeConnection()
{
    if (m_socket->isOpen()) {
            m_socket->close();
        }
}

void TCPClient::onConnected()
{
     emit connected();
}

void TCPClient::onDisconnected()
{
    emit disconnected();
}

void TCPClient::onDataReceived()
{
    emit dataReceived(m_socket->readAll());
}
