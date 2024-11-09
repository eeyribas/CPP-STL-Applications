#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class SerialPort
{
public:
    bool Open(std::string port_path, int baud_rate);
    bool IsOpen();
    void Close();
    std::vector<unsigned char> Read(uint length, unsigned char first_byte, unsigned char second_byte);

private:
    const int error_count = 25;
    const unsigned char error_data_code = 0;
    const unsigned char error_usb_code = 255;

    int fd = -1;
};

#endif // SERIALPORT_H