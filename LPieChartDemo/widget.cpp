#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("piechartDemo(devstone)");

    QVector<double> values(4);
    QVector<QColor> colors(4);

    colors[0] = Qt::red, colors[1] = Qt::blue,colors[2] = Qt::green,colors[3] = Qt::yellow;
    values[0] = 3.4, values[1] = 7.4,values[2] = 4.8, values[3] = 5.1;

    ui->widget_2->setData(values,colors);
}

Widget::~Widget()
{
    delete ui;
}
