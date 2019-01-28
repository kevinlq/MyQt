#include "viewgroup.h"
#include "icore.h"
#include "iview.h"
#include "mainwindow.h"
#include <QStackedLayout>
#include <QLabel>
#include <QDebug>
#include <QToolButton>
#include <QApplication>

using namespace RadarDisplay;

ViewGroup::ViewGroup(QWidget *parent) :
    QWidget(parent)
{
    m_stackLayout = new QStackedLayout(this);
    m_stackLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *label = new QLabel(tr("No active view."), this);
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_stackLayout->addWidget(label);
}

void ViewGroup::addView(IView *view)
{
    if (m_views.indexOf(view) != -1)
        return;
    m_views.append(view);
    m_stackLayout->addWidget(view);
}

void ViewGroup::removeView(IView *view)
{
    int idx = m_views.indexOf(view);
    if (idx == -1)
        return;
    m_views.removeAt(idx);
    m_stackLayout->removeWidget(view);
    view->setParent(0);
}

QList<IView *> ViewGroup::viewList() const
{
    return m_views;
}

void ViewGroup::setView(IView *view)
{
    m_stackLayout->setCurrentWidget(view);
}
