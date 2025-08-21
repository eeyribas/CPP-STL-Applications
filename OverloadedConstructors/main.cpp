#include <QCoreApplication>
#include <iostream>
#include "datacontent.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "----------------------------------------" << std::endl;

    DataContent data_content_1;
    std::cout << "Value-1 : " << data_content_1.value_1
              << std::endl;
    std::cout << "Value-2 : " << data_content_1.value_2
              << std::endl;
    std::cout << "Value-3 : " << data_content_1.value_3
              << std::endl;
    std::cout << "Value-4 (0.) : " << data_content_1.value_4[0]
              << std::endl;
    std::cout << "Value-4 (1.) : " << data_content_1.value_4[1]
              << std::endl;
    std::cout << "Value-4 (2.) : " << data_content_1.value_4[2]
              << std::endl;
    std::cout << "Value-5 : " << data_content_1.value_5
              << std::endl;
    std::cout << "----------------------------------------"
              << std::endl;

    DataContent data_content_2(205);
    std::cout << "Value-1 : " << data_content_2.value_1
              << std::endl;
    std::cout << "Value-2 : " << data_content_2.value_2
              << std::endl;
    std::cout << "Value-3 : " << data_content_2.value_3
              << std::endl;
    std::cout << "Value-4 (0.) : " << data_content_2.value_4[0]
              << std::endl;
    std::cout << "Value-4 (1.) : " << data_content_2.value_4[1]
              << std::endl;
    std::cout << "Value-4 (2.) : " << data_content_2.value_4[2]
              << std::endl;
    std::cout << "Value-5 : " << data_content_2.value_5
              << std::endl;
    std::cout << "----------------------------------------"
              << std::endl;

    DataContent data_content_3(98, 324.5);
    std::cout << "Value-1 : " << data_content_3.value_1
              << std::endl;
    std::cout << "Value-2 : " << data_content_3.value_2
              << std::endl;
    std::cout << "Value-3 : " << data_content_3.value_3
              << std::endl;
    std::cout << "Value-4 (0.) : " << data_content_3.value_4[0]
              << std::endl;
    std::cout << "Value-4 (1.) : " << data_content_3.value_4[1]
              << std::endl;
    std::cout << "Value-4 (2.) : " << data_content_3.value_4[2]
              << std::endl;
    std::cout << "Value-5 : " << data_content_3.value_5
              << std::endl;
    std::cout << "----------------------------------------"
              << std::endl;

    DataContent data_content_4(14, 378.98, 43);
    std::cout << "Value-1 : " << data_content_4.value_1
              << std::endl;
    std::cout << "Value-2 : " << data_content_4.value_2
              << std::endl;
    std::cout << "Value-3 : " << data_content_4.value_3
              << std::endl;
    std::cout << "Value-4 (0.) : " << data_content_4.value_4[0]
              << std::endl;
    std::cout << "Value-4 (1.) : " << data_content_4.value_4[1]
              << std::endl;
    std::cout << "Value-4 (2.) : " << data_content_4.value_4[2]
              << std::endl;
    std::cout << "Value-5 : " << data_content_4.value_5
              << std::endl;
    std::cout << "----------------------------------------"
              << std::endl;

    double array_1[] = {76.56, 234.1, 9.63};
    DataContent data_content_5(56, 32.6, 908, array_1);
    std::cout << "Value-1 : " << data_content_5.value_1
              << std::endl;
    std::cout << "Value-2 : " << data_content_5.value_2
              << std::endl;
    std::cout << "Value-3 : " << data_content_5.value_3
              << std::endl;
    std::cout << "Value-4 (0.) : " << data_content_5.value_4[0]
              << std::endl;
    std::cout << "Value-4 (1.) : " << data_content_5.value_4[1]
              << std::endl;
    std::cout << "Value-4 (2.) : " << data_content_5.value_4[2]
              << std::endl;
    std::cout << "Value-5 : " << data_content_5.value_5
              << std::endl;
    std::cout << "----------------------------------------"
              << std::endl;

    double array_2[] = {19.19, 101.5, 72.46};
    DataContent data_content_6(59, 385.29, 7, array_2, true);
    std::cout << "Value-1 : " << data_content_6.value_1
              << std::endl;
    std::cout << "Value-2 : " << data_content_6.value_2
              << std::endl;
    std::cout << "Value-3 : " << data_content_6.value_3
              << std::endl;
    std::cout << "Value-4 (0.) : " << data_content_6.value_4[0]
              << std::endl;
    std::cout << "Value-4 (1.) : " << data_content_6.value_4[1]
              << std::endl;
    std::cout << "Value-4 (2.) : " << data_content_6.value_4[2]
              << std::endl;
    std::cout << "Value-5 : " << data_content_6.value_5
              << std::endl;
    std::cout << "----------------------------------------"
              << std::endl;

    return a.exec();
}
