#include <QCoreApplication>
#include <iostream>

void MOAFilter(double input_data[], int input_data_len, double output_data[])
{
    output_data[0] = input_data[0];
    output_data[1] = input_data[1];
    output_data[2] = input_data[2];
    output_data[3] = input_data[3];
    // MOA Factor Count = 4
    for (int i = 4; i < input_data_len; i++)
        output_data[i] = (input_data[i - 4] + input_data[i - 3] + input_data[i - 2] +
                          input_data[i - 1] + input_data[i]) / 5;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const int data_length = 10;
    double input_data[data_length] = {10.2, 23.6, 45.4, 52.8, 47.5, 49.6, 55.1, 50.6, 43.2, 38.7};
    double output_data[data_length];
    MOAFilter(input_data, data_length, output_data);
    std::cout << "Output Data = ";
    for (int i = 0; i < data_length; i++)
        std::cout << output_data[i] << " ";
    std::cout << std::endl;

    return a.exec();
}
