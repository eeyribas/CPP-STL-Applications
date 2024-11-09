#include <QCoreApplication>
#include <unistd.h>
#include "datalogger.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DataLogger* data_logger = new DataLogger();
    data_logger->Start(1);

    sleep(1);
    Logger::AddLog(static_cast<int>(DataLoggerType::kInfo), "Hello World - Info");
    Logger::AddLog(static_cast<int>(DataLoggerType::kException), "Hello World - Exception");
    sleep(3);

    data_logger->Stop();
    delete data_logger;

    return a.exec();
}
