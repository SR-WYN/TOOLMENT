#include "Logger.hpp"

using namespace std;

Logger::Logger(const string& log_path)
{
    log_file_.open(log_path, std::ios::out | std::ios::app);
    if (!log_file_.is_open())
    {
        cerr << "can not open log_path" << endl;
    }
}

Logger::~Logger()
{
    if (log_file_.is_open())
    {
        log_file_.close();
    }
}