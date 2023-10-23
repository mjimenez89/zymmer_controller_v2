#include "rfid.h"

RFID::RFID(QObject *parent)
    : RFIDSimpleSource{parent}
{
    qDebug()<<"Source Node Started";
    setPressViaje(false);
}
