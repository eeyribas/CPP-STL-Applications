#ifndef SHARED_H
#define SHARED_H

#include <iostream>
#include "tcpcomm.h"

class Shared
{
public:
    static void Initiliaze();

    static TCPComm tcp_comm;
};

#endif // SHARED_H
