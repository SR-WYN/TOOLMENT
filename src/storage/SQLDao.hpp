#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>
#include "Singleton.hpp"

using json = nlohmann::json;

struct UserConfig
{
    int id;
    std::string username;
    json config;
};

class SQLDao : public Singleton<SQLDao>
{
public:
    explicit SQLDao(const std::string& path);
    bool save(const UserConfig& info);
    std::optional<UserConfig> getByUsername(const std::string& username);
    bool deleteByUsername(const std::string& username);

private:
    std::unique_ptr<SQLite::Database> db_;
};