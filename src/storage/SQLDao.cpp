#include <iostream>
#include "SQLDao.hpp"

using namespace std;

SQLDao::SQLDao(const string& path)
{
    db_ = std::make_unique<SQLite::Database>(path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    if (!db_)
    {
        cerr << "sqlite is empty!";
        return;
    }
    db_->exec(R"(
        CREATE TABLE IF NOT EXISTS USER (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            config TEXT NOT NULL
        );
    )");
}

bool SQLDao::save(const UserConfig& info)
{
    if (!db_)
    {
        cerr << "sqlite is empty!";
        return false;
    }
    SQLite::Statement query(*db_, R"(
        INSERT INTO USER (username, config) VALUES (?, ?)
        ON CONFLICT(username) DO UPDATE SET config = excluded.config;    
    )");

    query.bind(1, info.username);
    query.bind(2, info.config.dump());
    return query.exec() > 0;
}

optional<UserConfig> SQLDao::getByUsername(const string& username)
{
    if (!db_)
    {
        cerr << "sqlite is empty!";
        return std::nullopt;
    }
    SQLite::Statement query(*db_, "SELECT id, username, config FROM USER WHERE username = ?;");
    query.bind(1, username);
    if (query.executeStep())
    {
        UserConfig user;
        user.id = query.getColumn(0).getInt();
        user.username = query.getColumn(1).getText();

        std::string config_json_str = query.getColumn(2).getText();
        user.config = json::parse(config_json_str);

        return user;
    }
    return nullopt;
}

bool SQLDao::deleteByUsername(const std::string& username)
{
    if (!db_)
    {
        cerr << "sqlite is empty!";
        return false;
    }

    SQLite::Statement query(*db_, "DELETE FROM user_config WHERE username = ?;");
    query.bind(1, username);
    return query.exec() > 0;
}