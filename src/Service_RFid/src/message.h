#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QByteArray>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    void setu8(char val);
    void setu16(int val);

signals:
public:
    unsigned char data[256];
   int  writeIndex;

};

#endif // MESSAGE_H
