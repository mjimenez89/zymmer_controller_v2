#include <QCoreApplication>
#include "microservicerfid.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MicroServiceRFID microService;
    return a.exec();
}
