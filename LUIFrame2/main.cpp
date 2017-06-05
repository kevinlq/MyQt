#include <QApplication>
#include <QTextCodec>

#include "ui/mainwidget.h"
#include "util/appinit.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

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

    QFile file(":/image/style.css");
    file.open (QFile::ReadOnly);
    QString css = QLatin1String(file.readAll ());
    qApp->setStyleSheet (css);

    AppInit init;
    init.init ();

    MainWidget w;
    w.show ();

    return app.exec ();
}
