#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <thread>
#include <mutex>
#include "tcpclient.h"

class Communication
{
public:
    void Start(int core_index);

private:
    void Process(int core_index);
    int CheckEthCable(const char *if_name);

    std::thread th;
    std::mutex mtx;

    TCPClient tcp_init;
    TCPClient tcp_receiver;
    TCPClient tcp_sender;

    int selected_core_2 = 2;
};

#endif // COMMUNICATION_H
