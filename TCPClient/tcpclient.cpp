#include "tcpclient.h"

TCPClient::TCPClient()
{
    try {
        tcp_open_status = false;
        conn_status = false;

        SetThreadState(false);
        SetConnStatus(false);

    } catch (std::exception& e) {
    }
}

void TCPClient::SetThreadState(bool value)
{
    th_state = value;
}

bool TCPClient::GetThreadState()
{
    return th_state;
}

void TCPClient::SetConnStatus(bool value)
{
    conn_status = value;
}

bool TCPClient::GetConnStatus()
{
    return conn_status;
}

void TCPClient::Stop()
{
    try {
        bool thread_status = GetThreadState();
        SetThreadState(false);
        SetConnStatus(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (thread_status)
            th.join();
    } catch (std::exception& e) {
    }
}

void TCPClient::Init(int core_index)
{
    try {
        tcp_open_status = false;
        SetThreadState(true);
        th = std::thread(&TCPClient::InitProcess, this, core_index);

    } catch (std::exception& e) {
    }
}

void TCPClient::InitProcess(int core_index)
{
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(core_index, &cpu);
    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        std::cout << "Erroring core selection." << std::endl;

    for (;;) {
        try {
            std::lock_guard<std::mutex> grd(mtx);

            if (GetThreadState()) {
                if (tcp_open_status) {

                    if (Shared::tcp_comm.Connection()) {
                        SetConnStatus(true);
                        break;
                    } else {
                        SetConnStatus(false);
                    }

                } else {
                    tcp_open_status = Shared::tcp_comm.Open();
                }
            } else {
                break;
            }

        } catch (std::exception& e) {
        }
    }
}

void TCPClient::Receiver(int core_index)
{
    try {
        SetThreadState(true);
        th = std::thread(&TCPClient::ReceiverProcess, this, core_index);
    } catch (std::exception& e) {
    }
}

void TCPClient::ReceiverProcess(int core_index)
{
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(core_index, &cpu);
    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        std::cout << "Erroring core selection." << std::endl;

    for (;;) {
        try {
            std::lock_guard<std::mutex> grd(mtx);

            if (GetThreadState()) {

                std::vector<unsigned char> receiver_list = Shared::tcp_comm.Receive(receiver_length);
                if (receiver_list.size() == receiver_length && !Shared::tcp_comm.ErrorControl(receiver_list)) {
                    // Receive the data correctly
                }
            } else {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

        } catch (std::exception& e) {
        }
    }
}

void TCPClient::Sender(int core_index)
{
    try {
        SetThreadState(true);
        th = std::thread(&TCPClient::SenderProcess, this, core_index);
    } catch (std::exception& e) {
    }
}

void TCPClient::SenderProcess(int core_index)
{
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(core_index, &cpu);
    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        std::cout << "Erroring core selection." << std::endl;

    std::vector<unsigned char> send_data;

    for (;;) {
        try {
            std::lock_guard<std::mutex> grd(mtx);

            if (GetThreadState()) {
                bool send_data_state = Shared::tcp_comm.Send(send_data);
                if (!send_data_state)
                    std::cout << "TCP Send data error." << std::endl;

            } else {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } catch (std::exception& e) {
        }
    }
}
