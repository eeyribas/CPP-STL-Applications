#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include "customqueue.h"

enum DataLoggerType
{
    kInfo = 0,
    kException = 1
};

class Logger
{
public:
    static CustomQueue<std::pair<int, std::string>> data_logger_queue;
    static void AddLog(int logger_type, std::string log);
};

#endif // LOGGER_H
