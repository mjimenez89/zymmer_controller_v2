#include "message.h"

Message::Message(QObject *parent)
    : QObject{parent}
{

    writeIndex=1;
}

void Message::setu8(char val)
{
    data[writeIndex++]=val;
}

void Message::setu16(int val)
{

}
