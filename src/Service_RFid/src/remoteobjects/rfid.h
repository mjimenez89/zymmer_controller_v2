#ifndef RFID_H
#define RFID_H

#include <QObject>
#include "rep_rfid_source.h"

class RFID : public RFIDSimpleSource
{
    Q_OBJECT
public:
    explicit RFID(QObject *parent = nullptr);
};

#endif // RFID_H
