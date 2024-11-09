#include "fileoperations.h"

bool FileOperations::Control(std::string file_path)
{
    bool result = false;

    try {
        const char* c_file_path = file_path.c_str();
        FILE* file = fopen(c_file_path, "r");
        if (file) {
            result = true;
            fclose(file);
        } else {
            result = false;
        }

    } catch (std::exception& e) {
        result = false;
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(FileOperations Class) Control() function is not running. Error: " + std::string(e.what()));
    }

    return result;
}

bool FileOperations::Create(std::string file_path)
{
    bool result = false;

    try {
        std::ofstream file;
        file.open(file_path.c_str());
        file.close();
        result = true;

    } catch (std::exception& e) {
        result = false;
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(FileOperations Class) Create() function is not running. Error: " + std::string(e.what()));
    }

    return result;
}

long long int FileOperations::Size(std::string file_path)
{
    long long int file_size = 0;

    try {
        std::ifstream f_ptr(file_path, std::ios::binary);
        f_ptr.seekg(0, std::ios::end);
        file_size = f_ptr.tellg();

    } catch (std::exception& e) {
        file_size = 0;
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(FileOperations Class) Size() function is not running. Error: " + std::string(e.what()));
    }

    return file_size;
}

void FileOperations::Remove(std::string file_path)
{
    try {
        remove(file_path.c_str());
    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(FileOperations Class) Remove() function is not running. Error: " + std::string(e.what()));
    }
}

void FileOperations::Write(std::string file_path, std::string text)
{
    try {
        std::ofstream f_ptr;
        f_ptr.open(file_path, std::ofstream::out | std::ofstream::app);
        if (!f_ptr.is_open())
            Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(FileOperations Class) Write() fopen failed for input file.");
        else
            f_ptr << text << std::endl;
        f_ptr.close();

    } catch (std::exception& e) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(FileOperations Class) Write() function is not running. Error: " + std::string(e.what()));
    }
}

void FileOperations::WriteWithDateInfo(std::string file_path, std::string text)
{
    try
    {
        std::stringstream now_stream;
        time_t const now_time = time(nullptr);
        now_stream << std::put_time(localtime(&now_time), "%F %T");

        std::string dt = now_stream.str();
        std::string line = dt + " " + text;
        Write(file_path, line);
    }
    catch (std::exception& e)
    {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException), "(FileOperations Class) WriteWithDateInfo() function is not running. Error: " + std::string(e.what()));
    }
}
