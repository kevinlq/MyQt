#include "widget.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *code = QTextCodec::codecForName("UTF-8");
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForTr(code);
#else
    QTextCodec::setCodecForLocale(code);
    QTextCodec::setCodecForCStrings(code);
    QTextCodec::setCodecForTr(code);
#endif

    QFile file(":/image/black.css");
    file.open (QFile::ReadOnly);
    QString css = QLatin1String(file.readAll ());
    qApp->setStyleSheet (css);

    Widget w;
    w.show();

    return a.exec();
}
