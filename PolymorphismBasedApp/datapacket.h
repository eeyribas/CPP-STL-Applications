#ifndef DATAPACKET_H
#define DATAPACKET_H

#include "customqueue.h"

class DataPacket
{
public:
    void SetValue1(int value);
    int GetValue1();
    void SetValue2(int value);
    int GetValue2();

private:
    int value_1;
    int value_2;
};

#endif // DATAPACKET_H
