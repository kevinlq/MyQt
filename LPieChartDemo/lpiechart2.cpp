#include "lpiechart2.h"

#include <QPaintEvent>
#include <QPainter>

#include <qmath.h>

#include <QDebug>

//椭圆颜色
#define PIE_COLOR   QColor(11,100,100,255)
//椭圆半径
#define PIE_RADIUS  200.0

//线的颜色
#define LINE_COLOR QColor(45,11,11,255)

struct PieItemDataPrivate{
    QString pieName;
    int pieValue;
};


LPieChart2::LPieChart2(QWidget *parent)
    : QWidget(parent)
{
    init();
}

LPieChart2::~LPieChart2()
{
}

void LPieChart2::setData(QVector<double> value, QVector<QColor> colors)
{
    m_qvValues = value;
    m_qvColors = colors;

    repaint();
    update();
}

void LPieChart2::init()
{
}

void LPieChart2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    QRectF size;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    if (this->height() > this->width()){
        size = QRectF(5,5,this->width() - 10,this->width() - 10);
    }
    else{
        size = QRectF(5,5,this->height() - 10,this->height() - 10);
    }

    double sum = 0.0,startAng = 0.0;
    double angle,endAng,percent;

    for (int i = 0; i < m_qvValues.size(); i ++)
    {
        sum += m_qvValues.at(i);
    }
    for (int i = 0; i < m_qvValues.size(); i ++)
    {
        percent = m_qvValues.at(i) / sum;
        angle = percent * 360.0;
        endAng = startAng + angle;

        painter.setBrush(m_qvColors.at(i));
        painter.drawPie(size, startAng*16, angle * 16);

        startAng = endAng;
    }

    QWidget::paintEvent(event);
}

QSize LPieChart2::sizeHint() const
{
    //
}
