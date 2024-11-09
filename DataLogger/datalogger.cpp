#include "datalogger.h"

DataLogger::DataLogger()
{
    try {
        SetThreadState(false);
    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(DataLogger Class) DataLogger() function is not running. Error: " + std::string(e.what()));
    }
}

DataLogger::~DataLogger()
{
    try {
        Stop();
    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(DataLogger Class) ~DataLogger() function is not running. Error: " + std::string(e.what()));
    }
}

void DataLogger::SetThreadState(bool value)
{
    th_state = value;
}

bool DataLogger::GetThreadState()
{
    return th_state;
}

void DataLogger::Start(int core_index)
{
    try {
        SetThreadState(true);
        th = std::thread(&DataLogger::Run, this, core_index);
        Logger::AddLog(static_cast<int>(DataLoggerType::kInfo), "(DataLogger Class) Thread created.");

    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(DataLogger Class) Start() function is not running. Error: " + std::string(e.what()));
    }
}

void DataLogger::Stop()
{
    try {
        SetThreadState(false);
        th.join();
        Logger::AddLog(static_cast<int>(DataLoggerType::kInfo), "(DataLogger Class) Thread stopped.");

    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(DataLogger Class) Stop() function is not running. Error: " + std::string(e.what()));
    }
}

void DataLogger::Run(int core_index)
{
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(core_index, &cpu);

    if (sched_setaffinity(syscall(SYS_gettid),sizeof(cpu),&cpu) == -1)
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(SystemInfo Class) Erroring core selection.");

    for (;;) {
        try
        {
            std::lock_guard<std::mutex> grd(mtx);

            if (GetThreadState() == true) {

                int queue_count = Logger::data_logger_queue.count();
                if (queue_count > 0) {

                    if (file_operations.Size(info_path) > file_size) {
                        file_operations.Remove(info_path);
                        Control();
                    }

                    if (file_operations.Size(exception_path) > file_size) {
                        file_operations.Remove(exception_path);
                        Control();
                    }

                    for (int i = 0; i < queue_count; i++) {
                        std::pair<int, std::string> logger_q = Logger::data_logger_queue.getQueue();

                        if (logger_q.first == static_cast<int>(DataLoggerType::kInfo)) {
                            file_operations.WriteWithDateInfo(info_path, logger_q.second);
                            std::cout << logger_q.second << std::endl;
                        }
                        else if (logger_q.first == static_cast<int>(DataLoggerType::kException)) {
                            file_operations.WriteWithDateInfo(exception_path, logger_q.second);
                            std::cout << logger_q.second << std::endl;
                        }
                    }
                }
            } else {
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));

        } catch (std::exception& e) {
            Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(DataLogger Class) Run() function is not running. Error: " + std::string(e.what()));
        }
    }
}
