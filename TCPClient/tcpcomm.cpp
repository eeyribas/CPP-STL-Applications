#include "tcpcomm.h"

void TCPComm::SetIPAddress(std::string value){  ip_address = value;   }
void TCPComm::SetPortNo(uint16_t value) {  port_no = value;  }

bool TCPComm::Open()
{
    try {
        const char* c_ip_address = ip_address.c_str();
        struct hostent *host;

        if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
            return false;

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_no);

        if ((addr.sin_addr.s_addr = inet_addr(c_ip_address)) == INADDR_NONE) {
            if ((host = gethostbyname(c_ip_address)) == nullptr)
                 return false;

            memcpy(&addr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
        }

    } catch (std::exception& e) {
        return false;
    }

    return true;
}

bool TCPComm::Connection()
{
    try {
        struct timeval time;
        time.tv_sec = 0;
        time.tv_usec = 100000;
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&time, sizeof (timeval));

        if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
            return false;

    } catch (std::exception& e) {
        return false;
    }

    return true;
}

void TCPComm::Close()
{
    try {
        shutdown(sock, SHUT_RDWR);
        close(sock);
    } catch (std::exception& e) {

    }
}

bool TCPComm::Send(std::vector<unsigned char> data)
{
    try {
        unsigned char send_data[data.size()];
        int send_count = 0;
        int index_count = static_cast<int>(data.size());

        for (uint i = 0; i < data.size(); i++)
            send_data[i] = data.at(i);

        struct timeval time;
        time.tv_sec = 0;
        time.tv_usec = 100000;
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&time, sizeof (timeval));

        while (index_count != 0) {
            if ((send_count = send(sock, &send_data, index_count, false)) <= 0) {
                if (errno == EBADF) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    return false;
                }
            }

            if (send_count >= 0)
                index_count -= send_count;
        }

    } catch (std::exception& e) {
        return false;
    }

    return true;
}

std::vector<unsigned char> TCPComm::Receive(uint receive_size)
{
    std::vector<unsigned char> data;

    try {
        unsigned char receive_data[receive_size];
        int recv_count = 0;
        bool error_control = false;

        struct timeval time;
        time.tv_sec = 0;
        time.tv_usec = 100000;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&time, sizeof (timeval));

        if ((recv_count = recv(sock, &receive_data, receive_size, 0)) == -1) {
            if (errno == ECONNRESET)
                error_control = true;
            else if (errno == EBADF)
                error_control = true;
        }

        if (recv_count == static_cast<int>(receive_size) && !error_control) {
            for (uint i = 0; i < receive_size; i++)
                data.push_back(receive_data[i]);
        }

        if (error_control) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Close();
            data = ErrorStatus(receive_size);
        }

    } catch (std::exception& e) {
        data.clear();
    }

    return data;
}

std::vector<unsigned char> TCPComm::ErrorStatus(uint receive_size)
{
    std::vector<unsigned char> error_data;

    try {
        for (uint i = 0; i < receive_size; i++)
            error_data.push_back(0);

    } catch (std::exception& e) {

    }

    return error_data;
}

bool TCPComm::ErrorControl(std::vector<unsigned char> data)
{
    try {
        uint count = 0;

        for (uint i = 0; i < data.size(); i++) {
            if (data.at(i) == 0)
                count++;
        }

        if (count == data.size())
            return true;

    } catch (std::exception& e) {
        return false;
    }

    return false;
}