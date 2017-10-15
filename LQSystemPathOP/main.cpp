#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "systempathinfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SystemPathInfo>("L.Qt.SystemPathInfo",1,0,"SystemPathInfo");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
