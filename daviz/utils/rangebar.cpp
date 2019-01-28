#include "rangebar.h"
#include <QStyle>
#include <QPainter>
#include <QStyleOptionFrame>
#include <QMouseEvent>
#include <QToolTip>
#include <QDebug>

using namespace RadarDisplay;

namespace {
static const int INDICATOR_NARROW = 5;
static const int INDICATOR_WIDE = 9;
static const int GROOVE_WIDTH = 1;
static const int MARGIN = 2;
static const int MAJOR_TICK_WIDTH = 4;
static const int MINOR_TICK_WIDTH = 1;
}

RangeBar::RangeBar(Qt::Orientation orient, qreal min, qreal max, QWidget *parent) :
    QWidget(parent),
    m_orient(orient),
    m_rangeMin(min),
    m_rangeMax(max),
    m_rangeStart(min),
    m_rangeEnd(max),
    m_isDraggingStart(false),
    m_isDraggingEnd(false),
    m_isReversed(false),
    m_majorTicks(0),
    m_minorTicks(0)
{
    if (orient == Qt::Horizontal)
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    else
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

//    setAttribute(Qt::WA_AlwaysShowToolTips);
}

QSize RangeBar::sizeHint() const
{
    int w = MARGIN * 2 + INDICATOR_NARROW + GROOVE_WIDTH;
    QRect textRect;
    if (m_majorTicks) {
        w += MAJOR_TICK_WIDTH;
        textRect = fontMetrics().boundingRect(QString::number(m_rangeMax, 'f', 0));
    }
    if (m_orient == Qt::Horizontal) {
        return QSize(QWIDGETSIZE_MAX, w + textRect.height());
    } else {
        return QSize(w + textRect.width(), QWIDGETSIZE_MAX);
    }
}

void RangeBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    drawGroove(&p);
    drawTicks(&p);
    if (m_isDraggingStart)
        drawIndicator(m_rangeCurrent, &p, Qt::darkGray);
    else
        drawIndicator(m_rangeStart, &p);
    if (m_isDraggingEnd)
        drawIndicator(m_rangeCurrent, &p, Qt::darkGray);
    else
        drawIndicator(m_rangeEnd, &p);
    drawCover(&p);
}

qreal RangeBar::rangeMin() const
{
    return m_rangeMin;
}

qreal RangeBar::rangeMax() const
{
    return m_rangeMax;
}

void RangeBar::setRangeBound(qreal min, qreal max)
{
    m_rangeMin = min;
    m_rangeMax = max;
    updateGeometry();
    update();
}

qreal RangeBar::rangeStart() const
{
    return m_rangeStart;
}

qreal RangeBar::rangeEnd() const
{
    return m_rangeEnd;
}

bool RangeBar::isReversed() const
{
    return m_isReversed;
}

void RangeBar::setReversed(bool r)
{
    m_isReversed = r;
}

void RangeBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;
    if (hitTest(event->pos(), m_rangeStart)) {
        m_isDraggingStart = true;
        m_rangeCurrent = m_rangeStart;
        QString text = QString("Cur: %1").arg(m_rangeCurrent, 0, 'f', 2);
        QToolTip::showText(event->globalPos(), text, this);
        return;
    } else if (hitTest(event->pos(), m_rangeEnd)) {
        m_isDraggingEnd = true;
        m_rangeCurrent = m_rangeEnd;
        QString text = QString("Cur: %1").arg(m_rangeCurrent, 0, 'f', 2);
        QToolTip::showText(event->globalPos(), text, this);
        return;
    }
    qreal value;
    if (m_orient == Qt::Horizontal) {
        value = getValue(event->x());
    } else {
        value = getValue(event->y());
    }
    if (value <= m_rangeStart)
        setRange(value, m_rangeEnd);
    else if (value >= m_rangeEnd)
        setRange(m_rangeStart, value);
    else if (value - m_rangeStart < m_rangeEnd - value)
        setRange(value, m_rangeEnd);
    else
        setRange(m_rangeStart, value);
    QString text = QString("%1 - %2")
            .arg(m_rangeStart, 0, 'f', 2)
            .arg(m_rangeEnd, 0, 'f', 2);
    QToolTip::showText(event->globalPos(), text, this);
//    QToolTip::hideText();
}

void RangeBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    if (m_orient == Qt::Horizontal) {
        m_rangeCurrent = getValue(event->x());
    } else {
        m_rangeCurrent = getValue(event->y());
    }
//    QToolTip::hideText();
    QString text = QString("Cur: %1").arg(m_rangeCurrent, 0, 'f', 2);
    QToolTip::showText(event->globalPos(), text, this);
    update();
}

void RangeBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;
    qreal value;
    if (m_orient == Qt::Horizontal) {
        value = getValue(event->x());
    } else {
        value = getValue(event->y());
    }
    if (m_isDraggingStart) {
        if (value <= m_rangeEnd)
            setRange(value, m_rangeEnd);
        else
            setRange(m_rangeEnd, value);
        m_isDraggingStart = false;
    }
    if (m_isDraggingEnd) {
        if (m_rangeStart <= value)
            setRange(m_rangeStart, value);
        else
            setRange(value, m_rangeStart);
        m_isDraggingEnd = false;
    }
    update();
}

void RangeBar::setRangeStart(qreal start)
{
    setRange(start, m_rangeEnd);
}

void RangeBar::setRangeEnd(qreal end)
{
    setRange(m_rangeStart, end);
}

void RangeBar::setRange(qreal start, qreal end)
{
    if (start < m_rangeMin || end < start || m_rangeMax < end)
        return;
    m_rangeStart = start;
    m_rangeEnd = end;
    setToolTip(QString("%1 - %2\nMin: %3\nMax: %4")
               .arg(start, 0, 'f', 2)
               .arg(end, 0, 'f', 2)
               .arg(m_rangeMin, 0, 'f', 0)
               .arg(m_rangeMax, 0, 'f', 0));
    emit rangeChanged(start, end);
    update();
}

void RangeBar::setTicks(int majors, int minors)
{
    m_majorTicks = majors;
    m_minorTicks = minors;
    updateGeometry();
    update();
}

void RangeBar::drawGroove(QPainter *painter)
{
    painter->setPen(Qt::gray);
    if (m_orient == Qt::Horizontal) {
        painter->drawLine(QPoint(rect().left() + INDICATOR_NARROW + MARGIN, INDICATOR_NARROW + MARGIN),
                          QPoint(rect().right() - INDICATOR_NARROW - MARGIN, INDICATOR_NARROW + MARGIN));
    } else {
        painter->drawLine(QPoint(INDICATOR_NARROW + MARGIN, rect().top() + INDICATOR_NARROW + MARGIN),
                          QPoint(INDICATOR_NARROW + MARGIN, rect().bottom() - INDICATOR_NARROW - MARGIN));

    }
}

void RangeBar::drawTicks(QPainter *painter)
{
    if (m_majorTicks == 0)
        return;

    QPen pen(Qt::darkGray, 1);
    painter->setPen(pen);

    qreal len = (m_rangeMax - m_rangeMin);
    for (int i = 0; i <= m_majorTicks; i++) {
        qreal majorValue = m_rangeMin + len * i / m_majorTicks;
        int majorPos = getPos(majorValue);
        if (m_orient == Qt::Horizontal) {
            painter->drawLine(QPoint(majorPos, MARGIN + INDICATOR_NARROW + GROOVE_WIDTH),
                              QPoint(majorPos, MARGIN + INDICATOR_NARROW + GROOVE_WIDTH + MAJOR_TICK_WIDTH));
            QRectF textRect = fontMetrics().boundingRect(QString::number(majorValue, 'f', 0));
            textRect.translate(majorPos,
                               MARGIN + INDICATOR_NARROW + GROOVE_WIDTH + MAJOR_TICK_WIDTH + fontMetrics().height());
            painter->drawText(textRect,
                              QString::number(majorValue, 'f', 0));
        } else {
            painter->drawLine(QPoint(MARGIN + INDICATOR_NARROW + GROOVE_WIDTH, majorPos),
                              QPoint(MARGIN + INDICATOR_NARROW + GROOVE_WIDTH + MAJOR_TICK_WIDTH, majorPos));
            QRectF textRect = fontMetrics().boundingRect(QString::number(majorValue, 'f', 0));
            textRect.translate(MARGIN + INDICATOR_NARROW + GROOVE_WIDTH + MAJOR_TICK_WIDTH + fontMetrics().leading(),
                               majorPos);
            painter->drawText(textRect,
                              QString::number(majorValue, 'f', 0));
        }
        for (int j = 1; j < m_minorTicks; j++) {
            qreal minorValue = m_rangeMin + len * i / m_majorTicks + j * len / m_majorTicks / m_minorTicks;
            int minorPos = getPos(minorValue);
            if (m_orient == Qt::Horizontal) {
                painter->drawLine(QPoint(minorPos, MARGIN + INDICATOR_NARROW + GROOVE_WIDTH),
                                  QPoint(minorPos, MARGIN + INDICATOR_NARROW + GROOVE_WIDTH + MINOR_TICK_WIDTH));
            } else {
                painter->drawLine(QPoint(MARGIN + INDICATOR_NARROW + GROOVE_WIDTH, minorPos),
                                  QPoint(MARGIN + INDICATOR_NARROW + GROOVE_WIDTH + MINOR_TICK_WIDTH, minorPos));
            }

        }
    }
}

void RangeBar::drawIndicator(qreal rangeValue, QPainter *painter, QColor color)
{
    Q_ASSERT(m_rangeMax - m_rangeMin > 0);
    QPoint points[3];
    int pos = getPos(rangeValue);
    if (m_orient == Qt::Horizontal) {
        points[0] = QPoint(pos - INDICATOR_WIDE / 2, MARGIN);
        points[1] = QPoint(pos + INDICATOR_WIDE / 2, MARGIN);
        points[2] = QPoint(pos, INDICATOR_NARROW + MARGIN);
    } else {
        points[0] = QPoint(MARGIN, pos - INDICATOR_WIDE / 2);
        points[1] = QPoint(MARGIN, pos + INDICATOR_WIDE / 2);
        points[2] = QPoint(INDICATOR_NARROW + MARGIN, pos);
    }
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawConvexPolygon(points, 3);
}

void RangeBar::drawCover(QPainter *painter)
{
    int pos1, pos2;
    pos1 = getPos(m_rangeStart);
    pos2 = getPos(m_rangeEnd);
    if (m_isDraggingStart)
        pos1 = getPos(m_rangeCurrent);
    if (m_isDraggingEnd)
        pos2 = getPos(m_rangeCurrent);
    if (pos1 > pos2)
        qSwap(pos1, pos2);
    painter->setPen(Qt::green);
    if (m_orient == Qt::Horizontal) {
        painter->drawLine(QPoint(pos1, INDICATOR_NARROW + MARGIN),
                          QPoint(pos2, INDICATOR_NARROW + MARGIN));
    } else {
        painter->drawLine(QPoint(INDICATOR_NARROW + MARGIN, pos1),
                          QPoint(INDICATOR_NARROW + MARGIN, pos2));
    }
}

bool RangeBar::hitTest(const QPoint &pos, qreal rangeValue)
{
    int vpos = getPos(rangeValue);
    int p;
    if (m_orient == Qt::Horizontal)
        p = pos.x();
    else
        p = pos.y();
    return (qAbs(vpos - p) <= INDICATOR_NARROW);
}

int RangeBar::getPos(qreal rangeValue)
{
    Q_ASSERT(m_rangeMax - m_rangeMin > 0);
    int len;
    if (m_orient == Qt::Horizontal) {
        len = width();
    } else {
        len = height();
    }
    len -= 2 * INDICATOR_NARROW;
    len -= 2 * MARGIN;
    qreal value;
    if (m_isReversed)
        value = m_rangeMax - rangeValue;
    else
        value = rangeValue;
    int pos = (value - m_rangeMin) * len / (m_rangeMax - m_rangeMin) + INDICATOR_NARROW + MARGIN;
    return pos;
}

qreal RangeBar::getValue(int pos)
{
    Q_ASSERT(m_rangeMax - m_rangeMin > 0);
    int len;
    if (m_orient == Qt::Horizontal) {
        len = width();
    } else {
        len = height();
    }
    len -= 2 * INDICATOR_NARROW;
    len -= 2 * MARGIN;
    pos -= INDICATOR_NARROW;
    pos -= MARGIN;
    if (m_isReversed)
        pos = len - pos;
    if (pos <= 0)
        return m_rangeMin;
    if (pos >= len)
        return m_rangeMax;
    qreal value = pos * (m_rangeMax - m_rangeMin) / len;
    return value;
}
