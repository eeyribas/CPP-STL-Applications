#include <QCoreApplication>
#include <iostream>
#include "converter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Converter converter;
    std::cout << "Integer To String (123) -> " << converter.IntegerToString(123) << std::endl;
    std::cout << "Double To String (456.87) -> " << converter.DoubleToString(456.87) << std::endl;
    std::cout << "String To Integer ('8729') -> " << converter.StringToInteger("8729") << std::endl;
    std::cout << "String To Double ('4344.6') -> " << converter.StringToDouble("4344.6") << std::endl;
    std::cout << "Unsigned Char To String (201) -> " << converter.UnsignedCharToString(201) << std::endl;
    std::cout << "Convert Integer (657.6) -> " << converter.ConvertInteger(657.6) << std::endl;
    std::cout << "Convert Decimal (419.4) -> " << converter.ConvertDecimal(419.4) << std::endl;
    std::cout << "Unsigned Char 16Bit To Int (2, 8) -> " << converter.UnsignedChar16BitToInt(2, 8) << std::endl;
    std::cout << "Unsigned Char 32Bit To Int (5, 5, 9, 7) -> " << converter.UnsignedChar32BitToInt(5, 5, 9, 7) << std::endl;

    return a.exec();
}
