#include <QCoreApplication>
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;
using JSON = nlohmann::json;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string json_variables[] = {"Json1", "Json2", "Json3", "Json4"};

    string write_data_1 = "esen";
    int write_data_2 = 6;
    double write_data_3 = 10;
    bool write_data_4 = false;
    JSON write_json;
    write_json[json_variables[0]] = write_data_1;
    write_json[json_variables[1]] = write_data_2;
    write_json[json_variables[2]] = write_data_3;
    write_json[json_variables[3]] = write_data_4;
    ofstream write_file("key.json");
    write_file << write_json << std::endl;
    cout << "Writing..." <<endl;

    string read_data_1;
    int read_data_2;
    double read_data_3;
    bool read_data_4;
    ifstream read_file("key.json");
    JSON read_json = JSON::parse(read_file);
    read_data_1 = read_json.at(json_variables[0]).get<string>();
    read_data_2 = read_json.at(json_variables[1]).get<int>();
    read_data_3 = read_json.at(json_variables[2]).get<double>();
    read_data_4 = read_json.at(json_variables[3]).get<bool>();
    cout << read_data_1 << endl;
    cout << read_data_2 << endl;
    cout << read_data_3 << endl;
    cout << read_data_4 << endl;

    return a.exec();
}
