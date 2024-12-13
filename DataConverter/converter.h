#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <math.h>

class Converter
{
public:
    std::string IntegerToString(int value);
    std::string DoubleToString(double value);
    int StringToInteger(std::string value);
    double StringToDouble(std::string value);
    std::string UnsignedCharToString(unsigned char value);
    std::string UnsignedCharArrayToString(unsigned char value[], int lenght);
    void DoubleToCharArray(char value_char[], double value);
    void IntToCharArray(char value_char[], int value_int);
    int ConvertInteger(double value);
    int ConvertDecimal(double value);
    int HexadecimalToDecimal(char values[]);
    int UnsignedChar16BitToInt(unsigned char first, unsigned char second);
    int UnsignedChar32BitToInt(unsigned char first, unsigned char second, unsigned char third, unsigned char four);
};

#endif // CONVERTER_H
