#include "panelwidget.h"
#include "paneltitlebar.h"
#include <QAction>
#include <QPushButton>
#include <QDebug>
#include <QIcon>
#include <QToolBar>
#include <QToolButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QSplitter>
#include <QList>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

using namespace RadarDisplay;

static const int PANEL_EXTRA_TOP_MARGIN = 2;

PanelWidget::PanelWidget(QSplitter *parent) :
    QWidget(parent),
    m_widget(0),
    m_title(QString()),
    m_priority(0),
    m_viewContext(0),
    m_radarContext(0)
{
    init();
}

PanelWidget::PanelWidget(QWidget *widget, const QString &text, int priority, QSplitter *parent) :
    QWidget(parent),
    m_widget(widget),
    m_title(text),
    m_priority(priority),
    m_viewContext(0),
    m_radarContext(0)
{
    init();
}

PanelWidget::~PanelWidget()
{
}

QWidget *PanelWidget::widget() const
{
    return m_widget;
}

void PanelWidget::setWidget(QWidget *w)
{
    if (m_widget == w)
        return;
    toggleExpansion(false);
    m_widget = w;
    toggleExpansion(true);
}

QString PanelWidget::text() const
{
    return m_title;
}

void PanelWidget::setText(const QString &t)
{
    m_title = t;
}

int PanelWidget::priority() const
{
    return m_priority;
}

void PanelWidget::setPriority(int prio)
{
    if (m_priority != prio) {
        m_priority = prio;
        emit priorityChanged(prio);
    }
}

void PanelWidget::adjustSize(int contentHeight)
{
    if (!m_widget || !m_widget->isVisible())
        return;
    QSplitter *splitter = qobject_cast<QSplitter *>(parent());
    if (!splitter)
        return;
    int index = splitter->indexOf(this);
    if (index == -1)
        return;
    QList<int> sizes = splitter->sizes();
    int height = m_foldedHeight + contentHeight;
    if (sizes[index] != height) {
        sizes[index] = height;
        splitter->setSizes(sizes);
    }
}

void PanelWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    /*
    QStyleOptionButton option;
    option.initFrom(this);
    if (m_widget && m_widget->isVisible()) {
        option.state |= QStyle::State_On;
    }
    style()->drawControl(QStyle::CE_PushButton, &option, &p);
    */
    p.drawRoundedRect(rect().adjusted(2, 2, -2, -2), 2, 2);
}

void PanelWidget::enterEvent(QEvent *)
{
    update();
}

void PanelWidget::leaveEvent(QEvent *)
{
    update();
}

void PanelWidget::toggleExpansion(bool toggle)
{
    QSplitter *splitter = qobject_cast<QSplitter *>(parent());
    if (!splitter)
        return;
    int index = splitter->indexOf(this);
    if (index == -1)
        return;
    QList<int> sizes = splitter->sizes();
    if (toggle) {
        if (m_widget) {
            m_widget->show();
        }
//        setMinimumHeight(m_titleBar->sizeHint().height() + m_widget->minimumHeight());
        setMaximumHeight(m_expandedMaximumHeight);
        sizes[index] = m_expandedHeight;
        splitter->setSizes(sizes);
    } else {
        if (m_widget) {
            m_widget->hide();
        }
        m_expandedMaximumHeight = maximumHeight();
        setMaximumHeight(m_foldedHeight);
        m_expandedHeight = sizes[index];
        sizes[index] = m_foldedHeight;
        splitter->setSizes(sizes);
    }
    update();
}

void PanelWidget::init()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    int borderMargin = style()->pixelMetric(QStyle::PM_ButtonMargin);
    int extraTopMargin = PANEL_EXTRA_TOP_MARGIN;
    layout->setContentsMargins(borderMargin, borderMargin + extraTopMargin, borderMargin, borderMargin);
    layout->setSpacing(0);

    /*
    m_titleBar = new QToolBar(this);
    m_titleBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_titleBar->setContentsMargins(0, 0, 0, 0);
    m_expandButton = new PanelExpandWidget(this);
    connect(m_expandButton, SIGNAL(toggled(bool)), SLOT(toggleExpansion(bool)));
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QLabel *m_titleLabel = new QLabel(m_title, this);
    m_titleBar->addWidget(m_titleLabel);
    m_titleBar->addWidget(spacer);
    m_titleBar->addWidget(m_expandButton);
    m_foldedHeight = m_titleBar->sizeHint().height() + margin * 2;
    m_titleBar->setMaximumHeight(m_foldedHeight);
    layout->addWidget(m_titleBar);
    */

    m_titleBar = new PanelTitleBar(m_title, this);
    layout->addWidget(m_titleBar);

    m_foldedHeight = m_titleBar->height() + borderMargin * 2;

    m_expandedMaximumHeight = m_foldedHeight;
    if (m_widget) {
        layout->addWidget(m_widget);
        m_expandedHeight = sizeHint().height();
        if (m_widget->maximumHeight() < QWIDGETSIZE_MAX) {
            m_expandedMaximumHeight += m_widget->maximumHeight();
        } else {
            m_expandedMaximumHeight = QWIDGETSIZE_MAX;
        }
    }
    setMaximumHeight(m_expandedMaximumHeight);

    connect(m_titleBar, SIGNAL(toggled(bool)), SLOT(toggleExpansion(bool)));
}

IView *PanelWidget::viewContext() const
{
    return m_viewContext;
}

void PanelWidget::setViewContext(IView *view)
{
    m_viewContext = view;
}

IRadar *PanelWidget::radarContext() const
{
    return m_radarContext;
}

void PanelWidget::setRadarContext(IRadar *radar)
{
    m_radarContext = radar;
}
