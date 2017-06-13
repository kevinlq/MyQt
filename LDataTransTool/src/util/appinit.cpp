#include "appinit.h"

#include "config.h"

AppInit::AppInit(QObject *parent)
    : QObject(parent)
{

}

AppInit::~AppInit()
{
    //
}

void AppInit::setConfigPath(const QString &path)
{
    Config &config = Singleton<Config>::getInstance();
    config.setAppPath(path);
}

void AppInit::init()
{
    Config &config = Singleton<Config>::getInstance();
    config.loadDefaultInfo();
    config.conTest();
}
