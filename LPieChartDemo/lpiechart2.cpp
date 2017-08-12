#include "lpiechart2.h"

#include <QPaintEvent>
#include <QPainter>

#include <qmath.h>

#include <QDebug>

#define PIE_BOTTON_DIS  this->height() - 10
#define PIE_RIGHT_DIS   this->width() - 60
#define RECTANGLE_WIDTH 12.0

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

void LPieChart2::setData(QVector<double> value, QVector<QColor> colors,
                         QVector<QString> names)
{
    m_qvValues = value;
    m_qvColors = colors;
    m_qvName = names;

    repaint();
    update();
}

void LPieChart2::init()
{
    this->setMinimumSize(400,320);
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
        size = QRectF(5,5, PIE_BOTTON_DIS,PIE_BOTTON_DIS);
    }
    else{
        size = QRectF(5,5,PIE_BOTTON_DIS,PIE_BOTTON_DIS);
    }

    double sum = 0.0,startAng = 0.0;
    double angle,endAng,percent;
    qreal rectangleTop = 5;

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

        rectangleTop += 15;
        QRectF rectangle(PIE_RIGHT_DIS,rectangleTop, RECTANGLE_WIDTH, RECTANGLE_WIDTH);
        QRectF textF(PIE_RIGHT_DIS + RECTANGLE_WIDTH + 5,rectangleTop,70,10);
        painter.drawRect (rectangle);
        painter.drawText (textF,m_qvName.at (i));

        startAng = endAng;
    }

    QWidget::paintEvent(event);
}

