#ifndef DATAPATHS_H
#define DATAPATHS_H

#include <iostream>
#include "fileoperations.h"
#include "logger.h"

class DataPaths
{
public:
    DataPaths();
    void Control();

    std::string info_path = "InfoLog.txt";
    std::string exception_path = "ExceptionLog.txt";

private:
    FileOperations file_operations;
};

#endif // DATAPATHS_H
