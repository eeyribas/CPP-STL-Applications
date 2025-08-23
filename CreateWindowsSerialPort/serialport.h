#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class SerialPort
{
public:
    HANDLE Open(const char * device, uint32_t baud_rate);
    int Write(HANDLE port, uint8_t *buffer, size_t size);
    SSIZE_T Read(HANDLE port, uint8_t *buffer, size_t size);
    int JRKSetTarget(HANDLE handle, uint16_t target);
    int JRKGetVariable(HANDLE handle, uint8_t offset,
                       uint8_t *buffer, uint8_t length);
    int JRKGetTarget(HANDLE handle);
    int JRKGetFeedback(HANDLE handle);
    void PrintError(const char *context);
};

#endif // SERIALPORT_H
