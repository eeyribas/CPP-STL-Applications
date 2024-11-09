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
    }

    return file_size;
}

void FileOperations::Rename(std::string file_name_old, std::string file_name)
{
    try {
        rename(file_name_old.c_str(), file_name.c_str());
    } catch (std::exception& e) {
    }
}

void FileOperations::Remove(std::string file_path)
{
    try {
        remove(file_path.c_str());
    } catch (std::exception& e) {
    }
}

void FileOperations::WriteWithDateInfo(std::string file_path, std::string text)
{
    try {
        std::string dt = DateTimeNow();
        std::string line = dt + " " + text;
        Write(file_path, line);

    } catch (std::exception& e) {
    }
}

void FileOperations::Write(std::string file_path, std::string text)
{
    try {
        std::ofstream f_ptr;
        f_ptr.open(file_path, std::ofstream::out | std::ofstream::app);
        if (f_ptr.is_open())
            f_ptr << text << std::endl;
        f_ptr.close();

    } catch (std::exception& e) {
    }
}

std::vector<std::string> FileOperations::Read(std::string file_path)
{
    std::vector<std::string> lines;

    try {
        std::ifstream f_ptr;
        std::string tmp;

        f_ptr.open(file_path);
        if (!f_ptr.is_open()) {
            lines.clear();
        } else {
            while (getline(f_ptr, tmp))
                lines.push_back(tmp);
        }
        f_ptr.close();

    } catch (std::exception& e) {
        lines.clear();
    }

    return lines;
}

std::string FileOperations::DateTimeNow()
{
    std::string now = "";

    try {
        std::stringstream now_stream;
        time_t const now_time = time(nullptr);
        now_stream << std::put_time(localtime(&now_time), "%F %T");
        now = now_stream.str();

    } catch (std::exception& e) {
        now = "";
    }

    return now;
}
