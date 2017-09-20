#include "widget.h"
#include "ui_widget.h"

#include <QProcess>

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList environment = QProcess::systemEnvironment ();
    QString str;
    foreach (str, environment) {
        //if (str.startsWith ("PATH="))
        {
            qDebug()<<str<<endl;
            //break;
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
