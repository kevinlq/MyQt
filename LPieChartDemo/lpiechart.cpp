#include "lpiechart.h"

#include <QPaintEvent>
#include <QPainter>

#include <qmath.h>

#include <QDebug>

LPieChart::LPieChart(QWidget *parent) : QWidget(parent)
{

}

LPieChart::~LPieChart()
{
    //
}

void LPieChart::init()
{
    //
}

void LPieChart::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    // 去除画笔
    painter.setPen(Qt::NoPen);
    // 设置反锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    //******************************************** 圆饼图 *****************************************//
    // 顶层圆面
    QRectF rect_top(10.0, 20.0, 280.0, 160.0);
    // 底层圆面
    QRectF rect_bottom(10.0, 60.0, 280.0, 160.0);
    // 中间矩形
    QRectF rect_midd(10.0, 100.0, 280.0, 40.0);

    // 扇形起始角度
    int startAngle = 230 * 16;
    // 扇形覆盖范围
    int spanAngle = 60 * 16;

    painter.setBrush(QColor(251,100,100,255));
    // 绘制底层圆面
    painter.drawEllipse(rect_bottom);
    // 绘制中间矩形
    painter.drawRect(rect_midd);


    painter.setBrush(QColor(Qt::darkYellow));
    // 绘制底层扇形
    painter.drawPie(rect_bottom, startAngle, spanAngle);

    // 扇形的弦与弧的交点
    double pi = 3.1415926;
    double dx1 = rect_top.width() * 0.5 * cos(230 * pi / 180);
    double dy1 = rect_top.height() * 0.5 * sin(230 * pi / 180);

    double dx2 = rect_top.width() * 0.5 * cos(290 * pi / 180);
    double dy2 = rect_top.height() * 0.5 * sin(290 * pi / 180);


    // 求交点的坐标值
    QPointF posBackCenter = QPointF(rect_top.center());
    double dX1 = posBackCenter.x() + dx1 + 0.5;
    double dY1 = posBackCenter.y() - dy1 + 0.5;

    double dX2 = posBackCenter.x() + dx2 + 0.5;
    double dY2 = posBackCenter.y() - dy2 + 0.5;

    // 记录交点
    QPointF topLeft = QPointF(dX1, dY1);
    QPointF bottomRight = QPointF(dX2, dY2) + QPointF(0,40);
    QPointF bottomLeft = topLeft + QPointF(0,40);
    painter.setBrush(QColor(Qt::darkYellow));

    // 绘制连接扇形的区域
    QPolygonF path;
    path << topLeft << QPointF(dX2,dY2) << bottomRight << bottomLeft;
    painter.drawPolygon(path);

    // 绘制顶层圆面
    painter.setBrush(QColor(156,56,56,255));
    painter.drawEllipse(rect_top);

    // 绘制顶层扇形
    painter.setBrush(QColor(Qt::yellow));
    painter.drawPie(rect_top, startAngle, spanAngle);

    QWidget::paintEvent(ev);
}
