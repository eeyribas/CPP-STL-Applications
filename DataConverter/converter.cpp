#include "converter.h"

std::string Converter::IntegerToString(int value)
{
    std::string conv = std::to_string(value);

    return conv;
}

std::string Converter::DoubleToString(double value)
{
    std::string conv = std::to_string(value);

    return conv;
}

int Converter::StringToInteger(std::string value)
{
    int conv = stoi(value);

    return conv;
}

double Converter::StringToDouble(std::string value)
{
    double conv = stod(value);

    return conv;
}

std::string Converter::UnsignedCharToString(unsigned char value)
{
    int value_int = (int) value;
    std::string conv = std::to_string(value_int);

    return conv;
}

std::string Converter::UnsignedCharArrayToString(unsigned char value[], int lenght)
{
    std::string conv(value, value + lenght);

    return conv;
}

void Converter::DoubleToCharArray(char value_char[], double value)
{
    int count = 0;
    value = value * 10;
    int value_int = (int)value;

    while (value_int>0) {
        int tmp_value = value_int % 10;
        value_char[count] =  tmp_value + '0';
        value_int = value_int / 10;
        count++;
    }
}

void Converter::IntToCharArray(char value_char[], int value_int)
{
    int count = 0;
    while (value_int>0) {
        int tmp_value = value_int % 10;
        value_char[count] =  tmp_value + '0';
        value_int = value_int / 10;
        count++;
    }
}

int Converter::ConvertInteger(double value)
{
    int conv = (int) value;

    return conv;
}

int Converter::ConvertDecimal(double value)
{
    int integer_value_1 = (int) value;
    int integer_value_2 = (int) (value * 10);
    int conv = integer_value_2 - (integer_value_1 * 10);

    return conv;
}

int Converter::HexadecimalToDecimal(char values[])
{
    int len = 4;
    int base = 1;
    int dec_val = 0;

    for (int i = len - 1; i >= 0; i--) {
        if (values[i] >= '0' && values[i] <= '9') {
            dec_val += (values[i] - 48) * base;
            base = base * 16;
        } else if (values[i] >= 'A' && values[i] <= 'F') {
            dec_val += (values[i] - 55) * base;
            base = base * 16;
        }
    }

    return dec_val;
}

int Converter::UnsignedChar16BitToInt(unsigned char first, unsigned char second)
{
    int result = 0;
    int binary_first[8];
    int binary_second[8];

    for (int i = 0; i < 8; i++) {
        binary_first[i] = (first >> i) & 1;
        binary_second[i] = (second >> i) & 1;
    }

    for (int i = 0; i < 8; i++) {
        result += binary_first[i] * pow(2, i);
        result += binary_second[i] * pow(2, i + 8);
    }

    return result;
}

int Converter::UnsignedChar32BitToInt(unsigned char first, unsigned char second, unsigned char third, unsigned char four)
{
    int result = 0;
    int binary_first[8];
    int binary_second[8];
    int binary_third[8];
    int binary_four[8];

    for (int i = 0; i < 8; i++) {
        binary_first[i] = (first >> i) & 1;
        binary_second[i] = (second >> i) & 1;
        binary_third[i] = (third >> i) & 1;
        binary_four[i] = (four >> i) & 1;
    }


    for (int i = 0; i < 8; i++) {
        result += binary_first[i] * pow(2, i);
        result += binary_second[i] * pow(2, i + 8);
        result += binary_third[i] * pow(2, i + 16);
        result += binary_four[i] * pow(2, i + 24);
    }

    return result;
}
