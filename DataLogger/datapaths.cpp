#include "datapaths.h"

DataPaths::DataPaths()
{
    try {
        Control();
    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(DataPaths Class) DataPaths() function is not running. Error: " + std::string(e.what()));
    }
}

void DataPaths::Control()
{
    try {
        if (!file_operations.Control(info_path))
            file_operations.Create(info_path);

        if (!file_operations.Control(exception_path))
            file_operations.Create(exception_path);

    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(DataPaths Class) Control() function is not running. Error: " + std::string(e.what()));
    }
}
