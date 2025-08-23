#ifndef UDPCOMM_H
#define UDPCOMM_H

#include <stdio.h>
#include <iostream>
#include <vector>

#define PORT        65432
#define MAX_LINE    1024

class UDPComm
{
public:
     static int Setup();
     static int Send(std::vector<unsigned char> buffer);
     static std::vector<unsigned char> Recv();
     static void Close();

     static bool server_select;
     static char ip[];
};

#endif // UDPCOMM_H
