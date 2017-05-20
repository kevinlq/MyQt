#include <QApplication>

#include "ui/mainwidget.h"
#include "util/appinit.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    AppInit init;
    init.init ();

    MainWidget w;
    w.show ();

    return app.exec ();
}
