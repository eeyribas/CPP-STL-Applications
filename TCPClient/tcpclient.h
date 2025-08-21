#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <thread>
#include <mutex>
#include "shared.h"

class TCPClient
{
public:
    TCPClient();

    void Init(int core_index);
    void Receiver(int core_index);
    void Sender(int core_index);
    void Stop();

    void SetThreadState(bool value);
    bool GetThreadState();

    void SetConnStatus(bool value);
    bool GetConnStatus();

private:
    void InitProcess(int core_index);
    void ReceiverProcess(int core_index);
    void SenderProcess(int core_index);

    std::thread th;
    std::mutex mtx;
    bool th_state;

    bool conn_status;
    bool tcp_open_status;
    uint receiver_length = 2;
};

#endif // TCPCLIENT_H
