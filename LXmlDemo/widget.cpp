#include "widget.h"
#include "ui_widget.h"

#include "parsedom.h"
#include "svgparsedom.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //QString fileName = QApplication::applicationDirPath ()+"/person.xml";
    QString fileName = QApplication::applicationDirPath ()+"/WeChat.svg";
//    ParseDom dom;
//    dom.parse (fileName);

//    dom.parse2 (fileName);
    SVGParsedom svg;
    svg.parse (fileName);
}

Widget::~Widget()
{
    delete ui;
}
