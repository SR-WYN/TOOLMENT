#include "ConfigDao.hpp"
#include <fstream>
#include <iostream>

using namespace std;

ConfigDao::ConfigDao(const string& path)
{
    ifstream in(path);
    if (!in.is_open())
    {
        cerr << "can not open file: " << path << endl;
        return;
    }
    in >> config_;
}

string ConfigDao::getValue(string& key)
{
    return config_.value(key, "");
}