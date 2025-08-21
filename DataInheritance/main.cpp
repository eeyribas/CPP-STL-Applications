#include <QCoreApplication>
#include <iostream>
#include "deriveddata.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DerivedData *derived_data = new DerivedData();
    derived_data->SetValue(2);

    std::cout << "Derived Get Data : " << derived_data->GetValue()
              << std::endl;
    std::cout << "Derived Get Base Data : " << derived_data->GetBaseValue()
              << std::endl;
    std::cout << "Base Value Data : " << derived_data->BaseValue()
              << std::endl;

    delete derived_data;

    return a.exec();
}
