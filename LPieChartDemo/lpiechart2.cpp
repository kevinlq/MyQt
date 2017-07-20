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

void LPieChart2::setPieItems(const QString &name, const int &index)
{
    PieItemDataPrivate pieItem;
    pieItem.pieName = name;
    pieItem.pieValue = index;

    m_itemList.append(pieItem);
}

void LPieChart2::init()
{
}

void LPieChart2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    //椭圆
    QRectF rect_top(10.0,20.0,PIE_RADIUS,PIE_RADIUS);
    painter.setBrush(QColor(PIE_COLOR));

    //绘制椭圆
    painter.drawEllipse(rect_top);

    //绘制图标指示
    painter.setBrush(QColor(LINE_COLOR));

    QPolygonF polygon;
    polygon << QPointF(10.0,20.0) << QPointF(20.2, 30.2);

    painter.drawPolyline(polygon);


    //根据list绘制等分数目
    int count = m_itemList.count();
    if (count > 0){
        int startAngle = 30 * 16;
        int spanAngle = 45 * 16;
    }
    QWidget::paintEvent(event);
}
