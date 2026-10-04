#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Logger
{
public:
    explicit Logger(const std::string& log_path);
    ~Logger();

    std::ofstream* get_file()
    {
        return &log_file_;
    }

private:
    std::ofstream log_file_;
};

class LogMessage
{
public:
    LogMessage(std::ofstream* file, const std::string& level_str)
        : file_(file)
    {
        stream_ << "[" << level_str << "] ";
    }

    ~LogMessage()
    {
        if (file_ && file_->is_open())
        {
            *file_ << stream_.str() << std::endl;
        }
    }

    template <typename T> LogMessage& operator<<(const T& val)
    {
        stream_ << val;
        return *this;
    }

private:
    std::ofstream* file_ = nullptr;
    std::ostringstream stream_;
};