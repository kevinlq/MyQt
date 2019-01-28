#include "fancytabwidget.h"
#include <QTabBar>
#include <QDebug>
using namespace RadarDisplay;

FancyTabWidget::FancyTabWidget(QWidget *parent) :
    QTabWidget(parent),
    m_isEmpty(true),
    m_widget(0)
{
}

void FancyTabWidget::setPlaceHolderText(const QString &text)
{
    m_text = text;
    updateEmptyTab();
}

void FancyTabWidget::setPlaceHolderIcon(const QIcon &icon)
{
    m_icon = icon;
    updateEmptyTab();
}

void FancyTabWidget::setPlaceHolderWidget(QWidget *widget)
{
    m_widget = widget;
    updateEmptyTab();
}

void FancyTabWidget::setPlaceHolder(QWidget *widget, const QIcon &icon, const QString &text)
{
    m_widget = widget;
    m_icon = icon;
    m_text = text;
    updateEmptyTab();
}

void FancyTabWidget::setPlaceHolder(QWidget *widget, const QString &text)
{
    m_widget = widget;
    m_text = text;
    updateEmptyTab();
}

void FancyTabWidget::tabInserted(int index)
{
    Q_UNUSED(index)
    if ((count() == 1) && (widget(0) == m_widget))
        return;
    if (m_isEmpty) {
        m_isEmpty = false;
        updateEmptyTab();
    }
}

void FancyTabWidget::tabRemoved(int index)
{
    Q_UNUSED(index)
    if (count() == 0) {
        m_isEmpty = true;
        updateEmptyTab();
    }
}

void FancyTabWidget::updateEmptyTab()
{
    if (m_isEmpty) {
        if (count() == 0) {
            if (m_widget) {
                addTab(m_widget, m_icon, m_text);
                setTabsClosable(false);
            }
        } else {
            removeTab(0);
            if (m_widget) {
                addTab(m_widget, m_icon, m_text);
                setTabsClosable(false);
            }
        }
    } else {
        if (count() > 1) {
            removeTab(0);
            setTabsClosable(true);
        }
    }
}
