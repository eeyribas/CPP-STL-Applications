#include "boardv1.h"

bool BoardV1::Open()
{
    bool state = false;

    try {
        state = serial_port.Open(GetPortName(), GetBaudRate());
    } catch (std::exception& e) {
        state = false;
    }

    return state;
}

bool BoardV1::IsOpen()
{
    bool state = false;

    try {
        state = serial_port.IsOpen();
    } catch (std::exception& e) {
        state = false;
    }

    return state;
}

void BoardV1::Close()
{
    try {
        serial_port.Close();
    } catch (std::exception& e) {

    }
}

std::vector<unsigned char> BoardV1::Read()
{
    std::vector<unsigned char> data;

    try {
        data = serial_port.Read(GetDataLength(), GetSensorId1(), GetSensorId2());
    } catch (std::exception& e) {
        data.clear();
    }

    return data;
}
