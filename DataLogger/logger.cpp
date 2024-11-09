#include "logger.h"

CustomQueue<std::pair<int, std::string>> Logger::data_logger_queue;

void Logger::AddLog(int logger_type, std::string log)
{
    try {
        data_logger_queue.putQueue(std::pair<int, std::string>(logger_type, log));
    } catch (std::exception& e) {
        data_logger_queue.putQueue(std::pair<int, std::string>(DataLoggerType::kException, "(LoggerReader Class) AddLog() function is not running. Error: " + std::string(e.what())));
    }
}
