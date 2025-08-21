#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <thread>
#include <mutex>

class Process
{
public:
    Process();
    ~Process();

    void Start(int core_index, std::string text);
    void Stop();
    void SetThreadState(bool value);
    bool GetThreadState();

private:
    void ProcessFunction(int core_index, std::string text);

    std::thread th;
    std::mutex mtx;
    bool th_state;
};

#endif // PROCESS_H
