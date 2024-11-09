#include <QCoreApplication>
#include "serialport.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SerialPort *serial_port = new SerialPort();
    serial_port->Open("/dev/ttyUSB1", 9600);
    if (serial_port->IsOpen()) {
        std::vector<char> write_data = {'a', 'b', 'c', 'd', 'e'};
        serial_port->Write(write_data);

        std::vector<unsigned char> read_data = serial_port->Read(20);
        std::cout << "Read Data : ";
        for (uint i = 0; i < read_data.size(); i++)
            std::cout << read_data.at(i) << " ";
        std::cout << std::endl;
    }
    serial_port->Close();

    delete serial_port;

    return a.exec();
}
