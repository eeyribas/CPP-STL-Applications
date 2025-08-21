#include "serialport.h"
#include <thread>
#include <chrono>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

bool SerialPort::Open(std::string port_path, int baud_rate)
{
    bool state = false;

    if (IsOpen())
        Close();

    const char* c_port_path = port_path.c_str();
    fd = open(c_port_path, O_RDWR | O_NOCTTY | O_SYNC);

    struct termios tty;
    if (tcgetattr(fd, &tty) < 0) {
        fd = -1;
        state = false;
    }

    if (baud_rate == 9600) {
        cfsetospeed(&tty, (speed_t)B9600);
        cfsetispeed(&tty, (speed_t)B9600);
    } else if (baud_rate == 230400) {
        cfsetospeed(&tty, (speed_t)B230400);
        cfsetispeed(&tty, (speed_t)B230400);
    } else if (baud_rate == 3000000) {
        cfsetospeed(&tty, (speed_t)B3000000);
        cfsetispeed(&tty, (speed_t)B3000000);
    }

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1000;

    if ((tcsetattr(fd, TCSANOW, &tty)) != 0) {
        fd = -1;
        state = false;
    }
    tcflush(fd, TCIFLUSH);
    state = true;

    return state;
}

bool SerialPort::IsOpen()
{
    if (fd >= 0)
        return true;

    return false;
}

void SerialPort::Close()
{
    close(fd);
    fd = -1;
}

std::vector<unsigned char> SerialPort::Read(uint length, unsigned char first_byte,
                                            unsigned char second_byte)
{
    std::vector<unsigned char> read_data;
    unsigned char buffer[length];
    int num_to_read = static_cast<int>(length);
    int read_data_length = 0;
    int total_read = 0;

    while (num_to_read > 0) {
        read_data_length = read(fd, &buffer[total_read], num_to_read);

        if (read_data_length > 0 && (buffer[0] == first_byte ||
            buffer[0] == second_byte)) {
            total_read += read_data_length;
            num_to_read -= read_data_length;
        }
    }

    for (uint i = 0; i < length; i++)
        read_data.push_back(buffer[i]);

    return read_data;
}
