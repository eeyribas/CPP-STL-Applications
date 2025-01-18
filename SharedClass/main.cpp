#include <QCoreApplication>
#include "shared.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Shared::Initiliaze();

    return a.exec();
}
