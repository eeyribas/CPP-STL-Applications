#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>
#include "logger.h"

class FileOperations
{
public:
    bool Control(std::string file_path);
    bool Create(std::string file_path);
    long long int Size(std::string file_path);
    void Remove(std::string file_path);
    void Write(std::string file_path, std::string text);
    void WriteWithDateInfo(std::string file_path, std::string text);
};

#endif // FILEOPERATIONS_H
