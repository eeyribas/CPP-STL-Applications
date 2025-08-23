#include <QCoreApplication>
#include "serialport.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SerialPort serial_port;
    const char *device = "\\\\.\\COM8";
    uint32_t baud_rate = 3000000;

    HANDLE handle = serial_port.Open(device, baud_rate);
    if (handle == INVALID_HANDLE_VALUE)
        return 1;

    int feedback = serial_port.JRKGetFeedback(handle);
    if (feedback < 0)
        return 1;
    printf("Feedback is %d.\n", feedback);

    int target = serial_port.JRKGetTarget(handle);
    if (target < 0)
        return 1;
    printf("Target is %d.\n", target);

    int new_target = (target < 2048) ? 2248 : 1848;
    printf("Setting target to %d.\n", new_target);
    int result = serial_port.JRKSetTarget(handle, new_target);
    if (result)
        return 1;

    CloseHandle(handle);

    return a.exec();
}
