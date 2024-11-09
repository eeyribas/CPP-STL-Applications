#include <QCoreApplication>
#include "process.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Process *process = new Process();
    process->Start(1, "Hello World!");

    std::this_thread::sleep_for(std::chrono::seconds(10));
    process->Stop();

    if (process)
        delete process;

    return a.exec();
}
