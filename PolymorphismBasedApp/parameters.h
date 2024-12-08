#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>
#include "datapacket.h"
#include "customqueue.h"

class Parameters
{
public:
    inline static int type = 1;
    inline static DataPacket data_packet;
    inline static CustomQueue<DataPacket> custom_queue;
};

#endif // PARAMETERS_H
