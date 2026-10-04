#include "ConfigManager.hpp"
#include "ConfigDao.hpp"
#include "Logger.hpp"
#include "SQLDao.hpp"
#include "const.h"
#include <QCoreApplication>
#include <filesystem>
#include <fstream>

using namespace std;
using json = nlohmann::json;

ConfigManager::ConfigManager() = default;

ConfigManager::~ConfigManager() = default;

bool ConfigManager::init(const string& config_name)
{
    root_path_ = QCoreApplication::applicationDirPath().toStdString();

    // 配置文件路径
    filesystem::path config_path = filesystem::path(root_path_) / config_name;
    ifstream in(config_path);
    if (!in.is_open())
    {
        cerr << "can not open file: " << config_path << endl;
        return false;
    }

    config_ = make_unique<ConfigDao>(config_path);

    // 日志系统
    string log_path_key = LOG_PATH_KEY;
    string log_path = getConfigValue(log_path_key);
    log_path = filesystem::path(root_path_) / log_path;
    filesystem::path log_dir = filesystem::path(log_path).parent_path();
    if (!log_dir.empty() && !filesystem::exists(log_dir))
    {
        filesystem::create_directories(log_dir);
    }
    logger_ = make_unique<Logger>(log_path);

    // 数据库
    string db_path_key = DB_PATH_KEY;
    string db_path = getConfigValue(db_path_key);
    db_path = filesystem::path(root_path_) / db_path;
    sql_ = make_unique<SQLDao>(db_path);

    LOG_INFO << "ConfigManager init success";
    return true;
}

string ConfigManager::getConfigValue(string& key)
{
    return config_->getValue(key);
}