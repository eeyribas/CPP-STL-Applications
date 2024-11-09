#include <QCoreApplication>
#include "fileoperations.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string file_path = "File.txt";
    FileOperations file_operations;

    std::cout << "File Control : " << file_operations.Control(file_path) << std::endl;
    std::cout << "File Create : " << file_operations.Create(file_path) << std::endl;

    file_operations.Write(file_path, "Hello");
    file_operations.WriteWithDateInfo(file_path, "World");
    std::cout << "File written." << std::endl;

    std::cout << "File Size : " << file_operations.Size(file_path) << std::endl;

    std::vector<std::string> reader = file_operations.Read(file_path);
    for (uint i = 0; i < reader.size(); i++)
        std::cout << "File Read : " << reader.at(i) << std::endl;

    std::string new_file_path = "File2.txt";
    file_operations.Rename(file_path, new_file_path);
    std::cout << "File renamed." << std::endl;

    file_operations.Remove(new_file_path);
    std::cout << "File removed." << std::endl;

    return a.exec();
}
