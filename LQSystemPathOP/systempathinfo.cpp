#include "systempathinfo.h"

#include <QDebug>

SystemPathInfo::SystemPathInfo(QObject *parent)
    : QObject(parent)
{

}

SystemPathInfo::~SystemPathInfo()
{
}

void SystemPathInfo::slotOnSend()
{
    emit pathChanged ("This is Test PATH:///C/");
}
