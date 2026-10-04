#pragma once

#include "Singleton.hpp"
#include <memory>
#include <string>

class SQLDao;
class ConfigDao;
class Logger;

class ConfigManager : public Singleton<ConfigManager>
{
public:
    ConfigManager();
    ~ConfigManager();
    bool init(const std::string& config_name);
    std::string getConfigValue(std::string& key);

private:
    std::unique_ptr<SQLDao> sql_;
    std::unique_ptr<ConfigDao> config_;
    std::unique_ptr<Logger> logger_;
    std::string root_path_;
};

#define LOG_DEBUG LogMessage(ConfigManager::getInstance().logger_->->get_file(), "DEBUG")
#define LOG_INFO LogMessage(ConfigManager::getInstance().logger_->get_file(), "INFO")
#define LOG_WARN LogMessage(ConfigManager::getInstance().logger_->get_file(), "WARN")
#define LOG_ERROR LogMessage(ConfigManager::getInstance().logger_->get_file(), "ERROR")