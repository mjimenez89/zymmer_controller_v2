#include "tcpcontroller.h"
#include "message.h"

TCPController::TCPController(QObject *parent)
    : QObject{parent}
{
    m_client = new TCPClient(this);

        connect(m_client, &TCPClient::connected, this, &TCPController::connected);
        connect(m_client, &TCPClient::disconnected, this, &TCPController::disconnected);
        connect(m_client, &TCPClient::dataReceived, this, &TCPController::dataReceived);
}

TCPController::~TCPController()
{
    delete m_client;
}

void TCPController::connectToHost(const QString &host, quint16 port)
{
    m_client->connectToHost(host, port);
}

void TCPController::sendData(const QByteArray &data)
{
    m_client->sendData(data);
}

void TCPController::sendMessage(Message *msg)
{
    msg->data[0]=msg->writeIndex+1;
    int num =calcCrc(msg->data,msg->writeIndex);
    msg->setu8(num&0xFF);
    msg->setu8((num>>8)&0xFF);
    int writeIndex=msg->writeIndex;
    QByteArray arrr(reinterpret_cast<const char*>(msg->data),256);
    m_client->sendData(arrr);
}

void TCPController::closeConnection()
{
    m_client->closeConnection();
}

unsigned short TCPController::calcCrc(unsigned char message[], int length)
{
    unsigned short preset=65535;
    unsigned short polynomial=33800;
    unsigned short num=preset;
    for (int i = 0; i < length; ++i) {
        num=(unsigned short)(num^(message[i]&0xFF));
        for(int j=0;j<8;j++)
        {
            if(1==(num&1))
            {
                unsigned short num2=(unsigned short)((num>>1)^polynomial);
                num=num2;
            }
            else
            {
                num=(unsigned short)(num>>1);
            }
        }
    }
    return num;
}
