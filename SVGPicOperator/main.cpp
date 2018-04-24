#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "svgparsedom.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    SVGParsedom pa;
    QString strPath = QGuiApplication::applicationDirPath ()+"/we.svg";
    pa.parse (strPath);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
