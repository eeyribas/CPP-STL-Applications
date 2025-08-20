#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

class FileOperations
{
public:
    bool Control(std::string file_path);
    bool Create(std::string file_path);
    long long int Size(std::string file_path);
    void Rename(std::string file_name_old, std::string file_name);
    void Remove(std::string file_path);
    void WriteWithDateInfo(std::string file_path, std::string text);
    void Write(std::string file_path, std::string text);
    std::vector<std::string> Read(std::string file_path);

private:
    std::string DateTimeNow();
};

#endif // FILE_OPERATIONS_H
