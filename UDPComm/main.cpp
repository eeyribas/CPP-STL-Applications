#include <QCoreApplication>
#include "udpcomm.h"

class Params
{
public:
    unsigned char param_1;
    unsigned char param_2;
    unsigned char param_3;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UDPComm::server_select = false; //client = 0
    UDPComm::Setup();

    Params params;
    params.param_1 = 1;
    params.param_2 = 2;
    params.param_3 = 3;

    std::vector<unsigned char> buffer;
    buffer.push_back(params.param_1);
    buffer.push_back(params.param_1);
    buffer.push_back(params.param_1);

    while (true) {
        std::cout << "Server Select : " << UDPComm::server_select
                  << std::endl;
        UDPComm::Send(buffer);
        std::cout << "UDP send.\n" << std::endl;
        getchar();
    }

    UDPComm::Close();

    return a.exec();
}
