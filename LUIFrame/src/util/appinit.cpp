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

void AppInit::init()
{
    Config &config = Singleton<Config>::getInstance();
    config.loadDefaultInfo();
//    config.conTest();
}
