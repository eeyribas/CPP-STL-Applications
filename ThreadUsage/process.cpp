#include "process.h"

Process::Process()
{
    try {
        Stop();
    } catch (std::exception& e) {
    }
}

Process::~Process()
{
    try {
        Stop();
    } catch (std::exception& e) {
    }
}

void Process::Start(int core_index, std::string text)
{
    try {
        Stop();
        SetThreadState(true);
        th = std::thread(&Process::ProcessFunction, this, core_index, text);
    } catch (std::exception& e) {
    }
}

void Process::Stop()
{
    try {
        bool thread_status = GetThreadState();
        SetThreadState(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (thread_status)
            th.join();
    } catch (std::exception& e) {
    }
}

void Process::SetThreadState(bool value)
{
    th_state = value;
}

bool Process::GetThreadState()
{
    return th_state;
}

void Process::ProcessFunction(int core_index, std::string text)
{
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(core_index, &cpu);

    if (sched_setaffinity(syscall(SYS_gettid),sizeof(cpu),&cpu) == -1)
        std::cout << "Erroring core selection." << std::endl;

    for (;;) {
        try {
            std::lock_guard<std::mutex> grd(mtx);
            if (GetThreadState()) {
                std::cout << "Text : " << text << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                break;
            }
        } catch (std::exception& e) {
        }
    }
}
