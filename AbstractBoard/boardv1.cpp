#include "boardv1.h"
#include <cmath>
#include <chrono>

bool BoardV1::Open()
{
    return serial_port.Open(GetPortName(), GetBaudRate());
}

bool BoardV1::IsOpen()
{
    return serial_port.IsOpen();
}

void BoardV1::Close()
{
    serial_port.Close();
}

std::vector<unsigned char> BoardV1::Read()
{
    return serial_port.Read(GetDataLength(), GetSensorId1(),
                            GetSensorId2());
}
