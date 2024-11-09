#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/statvfs.h>
#include "datapaths.h"
#include "logger.h"

class DataLogger : public DataPaths
{
public:
    DataLogger();
    ~DataLogger();

    void Start(int core_index);
    void Stop();
    void Run(int core_index);

private:
    std::thread th;
    std::mutex mtx;
    bool th_state;
    void SetThreadState(bool value);
    bool GetThreadState();

    FileOperations file_operations;

    long long int file_size = 300000000;
};

#endif // DATALOGGER_H
