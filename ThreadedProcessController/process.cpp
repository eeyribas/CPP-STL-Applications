#include "process.h"
#include <chrono>

Process::Process()
{
    state = false;
    std::cout << "Thread created." << std::endl;
}

Process::~Process()
{
    std::cout << "Thread finished." << std::endl;
}

void Process::Start(int process_type)
{
    state = true;
    if (process_type == static_cast<int>(ProcessesFuncType::kMethod1))
        th = std::thread(&Process::Method2, this);
}

void Process::Start(int process_type, int value)
{
    state = true;
    if (process_type == static_cast<int>(ProcessesFuncType::kMethod2))
        th = std::thread(&Process::Method1, this, value);
}

void Process::Stop()
{
    state = false;
    th.join();
    std::cout << "Thread finished." << std::endl;
}

void Process::Method1(int value)
{
    for (;;) {
        std::lock_guard<std::mutex> grd(mtx);

        if (state) {
            std::cout << "Value = " << value << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            std::cout << "Method1 finished." << std::endl;
            break;
        }
    }
}

void Process::Method2()
{
    for (;;) {
        std::lock_guard<std::mutex> grd(mtx);

        if (state) {
            std::cout << "Static..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            std::cout << "Method2 finished." << std::endl;
            break;
        }
    }
}
