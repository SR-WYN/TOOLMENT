#include "ConfigManager.hpp"
#include "const.h"
#include "mainwindow.h"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    
    QApplication a(argc, argv);
    auto& cfg_mgr = ConfigManager::getInstance();
    if (!cfg_mgr.init(CONFIG_NAME))
    {
        cerr << "can not init ConfigManager!" << endl;
        return -1;
    }
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
