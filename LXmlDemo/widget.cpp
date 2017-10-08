#include "widget.h"
#include "ui_widget.h"

#include "parsedom.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString fileName = QApplication::applicationDirPath ()+"/person.xml";

    ParseDom dom;
    dom.parse (fileName);

    dom.parse2 (fileName);
}

Widget::~Widget()
{
    delete ui;
}
