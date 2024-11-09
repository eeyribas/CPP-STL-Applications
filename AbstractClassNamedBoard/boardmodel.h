#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <iostream>
#include <vector>

class BoardModel
{
public:
    virtual ~BoardModel() = 0;
    virtual bool Open() = 0;
    virtual bool IsOpen() = 0;
    virtual void Close() = 0;
    virtual std::vector<unsigned char> Read() = 0;

    void SetPortName(std::string value);
    std::string GetPortName();
    void SetBaudRate(int value);
    int GetBaudRate();
    void SetDataLength(uint value);
    uint GetDataLength();
    void SetSensorId1(unsigned char id);
    unsigned char GetSensorId1();
    void SetSensorId2(unsigned char id);
    unsigned char GetSensorId2();

private:
    std::string port_name;
    int baud_rate;
    uint data_length;
    unsigned char sensor_id_1;
    unsigned char sensor_id_2;
};

#endif // BOARDMODEL_H
