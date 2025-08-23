#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <thread>
#include <mutex>

enum ProcessesFuncType
{
    kMethod1 = 0,
    kMethod2 = 1
};

class Process
{
public:
    Process();
    ~Process();

    void Start(int process_type);
    void Start(int process_type, int value);
    void Stop();

    void Method1(int value);
    void Method2();

private:
    std::thread th;
    std::mutex mtx;
    bool state;
};

#endif // PROCESS_H
