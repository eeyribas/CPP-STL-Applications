#include <QCoreApplication>
#include "communication.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Communication* commun = new Communication();
    commun->Start(1);
    std::this_thread::sleep_for(std::chrono::seconds(8));

    return a.exec();
}
