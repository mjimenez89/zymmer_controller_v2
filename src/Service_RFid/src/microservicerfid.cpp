#include "microservicerfid.h"
#include <QThread>
#include <QDateTime>

MicroServiceRFID::MicroServiceRFID(QObject *parent)
    : QObject{parent}
{
    pressViaje=rfid.pressViaje();
    //Ponemos el nodo para compatir
    srcNode.setHostUrl(QUrl(QStringLiteral("local:rfid")));
    if(srcNode.enableRemoting(&rfid))
        qDebug()<<"Se compartio el objeto remoto";


    /*HAcemos las conexiones necesarias para el funcionamiento del microServicio*/
    connect(&controller,&TCPController::connected,this,&MicroServiceRFID::frecuenciaConfig);
    connect(&controller,&TCPController::disconnected,this,&MicroServiceRFID::reConexion);
    connect(&fre,&QTimer::timeout,this,&MicroServiceRFID::sendMsg);
    connect(&controller, &TCPController::dataReceived,this,&MicroServiceRFID::processMsg);
    connect(&rfid,&RFID::pressViajeChanged,this,&MicroServiceRFID::updatePressViaje);

    // Nos conectamos al servidor
    controller.connectToHost("192.168.2.136", 8090);

//    //Configuramos el mensaje de consulta
//    msg->setu8(255);
//    msg->setu8(1);
//    msg->setu8(4);//Q
//    msg->setu8(1);//Session
//    msg->setu8(0);
//    msg->setu8(128);
//    msg->setu8(10);

}

void MicroServiceRFID::frecuenciaConfig()
{
    qDebug() << "Conectado al servidor.";
    fre.start(100);
}

void MicroServiceRFID::reConexion()
{
    qDebug() << "Desconectado del servidor.Intento de reconexion";
    QThread::sleep(100);
}

void MicroServiceRFID::sendMsg()
{
    Message *msg=new Message();

    msg->setu8(255);
    msg->setu8(1);
    msg->setu8(4);//Q
    msg->setu8(2);//Session
    msg->setu8(0);
    msg->setu8(128);
    msg->setu8(10);
    controller.sendMessage(msg);
}

void MicroServiceRFID::processMsg(const QByteArray &data)
{
    int num1=data.at(2);
    int num2=data.at(3);
    if(num1==1 & num2!=1)
    {
        int len=data.at(6);
        int ID=data.at(7+len-1);
        QByteArray array;
        array.resize(len);
        array=data.mid(7,len);
        QString hexString;
        hexString.reserve(array.length() * 2);
        for (int i = 0; i < array.length(); ++i) {
            hexString.append(QString::number(static_cast<unsigned char>(array[i]), 16).rightJustified(2, '0'));
        }
        qDebug()<<"RSSI: "<<hexString<<"TimeStamp"<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        /*Si estamos en presencia de viaje agregamos los RFid detectados a la lista para despues pasarselos al servicio principal*/
        if(pressViaje)
        {
            qDebug()<<"Rfid Agrgado";
            QStringList listTemp=rfid.msg();
            listTemp.append(hexString);
            rfid.setMsg(listTemp);
        }
    }
}

void MicroServiceRFID::updatePressViaje(bool pressViajeRFID)
{
    if(pressViajeRFID)
    {
        qDebug()<<"Borramos los rfid viejos";
        rfid.msg().clear();
    }
    else
    {
        qDebug()<<"Se dejan de registrar los Rfid";
    }
    if(pressViaje!=pressViajeRFID)
    {
        pressViaje=pressViajeRFID;
    }

}
