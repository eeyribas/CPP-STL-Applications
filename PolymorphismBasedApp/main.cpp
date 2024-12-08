#include <QCoreApplication>
#include "base.h"
#include "derived1.h"
#include "derived2.h"
#include "parameters.h"
#include "datapacket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Base *base;
    if (Parameters::type == 0) {
        Derived1 derived_1;
        base = &derived_1;
        base->Method1(5);
        base->Method2(true);
    } else if (Parameters::type == 1) {
        Derived2 derived_2;
        base = &derived_2;
        base->Method1(3);
        base->Method2(false);
    }

    Parameters::data_packet.SetValue1(9);
    std::cout << "Value 1 = " << Parameters::data_packet.GetValue1() << std::endl;
    Parameters::data_packet.SetValue2(6);
    std::cout << "Value 2 = " << Parameters::data_packet.GetValue2() << std::endl;

    DataPacket data_packet;
    data_packet.SetValue1(7);
    data_packet.SetValue2(8);
    Parameters::custom_queue.putQueue(data_packet);
    std::cout << "Queue Size = " << Parameters::custom_queue.count() << std::endl;

    return a.exec();
}
