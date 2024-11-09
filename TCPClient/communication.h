#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/statvfs.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <errno.h>
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
