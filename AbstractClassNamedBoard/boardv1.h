#ifndef BOARDV1_H
#define BOARDV1_H

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "boardmodel.h"
#include "serialport.h"

class BoardV1 : public BoardModel
{
public:
    ~BoardV1() { }
    bool Open();
    bool IsOpen();
    void Close();
    std::vector<unsigned char> Read();

private:
    SerialPort serial_port;
};

#endif // BOARDV1_H
