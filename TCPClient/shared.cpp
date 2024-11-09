#include "shared.h"

TCPComm Shared::tcp_comm;

void Shared::Initiliaze()
{
    tcp_comm.SetIPAddress("192.168.1.x");
    tcp_comm.SetPortNo(1234);
}
