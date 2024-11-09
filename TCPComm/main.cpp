#include <QCoreApplication>
#include "tcpcomm.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TCPComm *tcp_comm = new TCPComm();
    tcp_comm->SetIPAddress("192.168.1.x");
    tcp_comm->SetPortNo(12345);

    if (tcp_comm->Connection()) {
        if (tcp_comm->Open()) {
            std::vector<unsigned char> send_data = {1, 2, 3, 4, 5};
            bool send_data_status = tcp_comm->Send(send_data);
            std::cout << "Send Data Status : " << send_data_status << std::endl;

            std::vector<unsigned char> read_data = tcp_comm->Receive(100);
            std::cout << "Read Data : ";
            for (uint i = 0; i < read_data.size(); i++)
                std::cout << read_data.at(i) << " ";
            std::cout << std::endl;
        }
    }
    tcp_comm->Close();

    delete tcp_comm;

    return a.exec();
}
