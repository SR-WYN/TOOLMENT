#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

class ConfigDao
{
public:
    explicit ConfigDao(const std::string& path);
    std::string getValue(std::string& key);

private:
    json config_;
};