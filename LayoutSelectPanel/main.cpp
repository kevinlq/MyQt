#include "Widget.h"

#include <QApplication>
#include <QtDebug>


#include "LayoutSelectPanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QfwUtil::LayoutSelectPanel w;

    QObject::connect(&w, &QfwUtil::LayoutSelectPanel::signalSelectLayoutChange,[](int nRow, int nCol){
        qWarning() << "signalSelectLayoutChange " << nRow << nCol;
    });

    w.show();

//    Widget w;
//    w.show();
    return a.exec();
}
