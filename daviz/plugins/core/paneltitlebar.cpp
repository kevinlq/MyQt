#include "paneltitlebar.h"
#include <QPainter>
#include <QDebug>
#include <QStyle>
#include <QStyleOption>
#include <QPalette>
#include <QRect>
#include <QLinearGradient>
using namespace RadarDisplay;

PanelTitleBar::PanelTitleBar(const QString &text, QWidget *parent) :
    QWidget(parent),
    m_text(text),
    m_titleHeight(0),
    m_toggled(true),
    m_highlighted(false)
{
    QFont f = font();
    f.setBold(true);
    QFontMetrics fm(f);
    m_titleHeight = fm.height() + 2;
    setFixedHeight(m_titleHeight);
}

void PanelTitleBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont f = font();
    f.setBold(true);
    p.setFont(f);
    p.drawText(rect(), m_text);

    QStyleOption so;
    so.initFrom(this);
    so.rect = QRect(so.rect.right() - m_titleHeight, 0, m_titleHeight, m_titleHeight);
    so.rect.setHeight(m_titleHeight);
    if (underMouse())
        so.palette.setColor(QPalette::ButtonText, palette().highlightedText().color());
    if (m_toggled)
        style()->drawPrimitive(QStyle::PE_IndicatorArrowUp, &so, &p);
    else
        style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &so, &p);

}

void PanelTitleBar::enterEvent(QEvent *)
{
    m_highlighted = true;
    update();
}

void PanelTitleBar::leaveEvent(QEvent *)
{
    m_highlighted = false;
    update();
}

void PanelTitleBar::mousePressEvent(QMouseEvent *)
{
    m_toggled = !m_toggled;
    emit toggled(m_toggled);
}
