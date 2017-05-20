#include "mainwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include <QDebug>

#include "titleWidget/ltitlewidget.h"
#include "statusWidget/lstatuswidget.h"


MainWidget::MainWidget(QWidget *parent)
    : NBaseMoveableWidget(parent)
{
    init ();
}

MainWidget::~MainWidget()
{
#if DEBUG_OUT
    qDebug ()<<"destroy mainWidget!";
#endif
}

void MainWidget::init()
{
    initForm ();

    initWidget ();

    initConnect ();
}

void MainWidget::initForm()
{
    this->resize (840,600);

    //this->setWindowFlags(Qt::FramelessWindowHint);
    //setMouseTracking (true);
}

void MainWidget::initWidget()
{
    m_pTitleWidget = new LTitleWidget(this);

    m_pStatusWidget = new LStatusWidget(this);

    m_pStackedWidget = new QStackedWidget(this);

    m_pVMainLayout = new QVBoxLayout(this);
    m_pVMainLayout->addWidget (m_pTitleWidget);
    m_pVMainLayout->addWidget (m_pStackedWidget);
    m_pVMainLayout->addWidget (m_pStatusWidget);
    m_pVMainLayout->setContentsMargins (0,0,0,0);

    setLayout (m_pVMainLayout);
}

void MainWidget::initConnect()
{
    connect (m_pTitleWidget,SIGNAL(signalClose()),
             this,SLOT(slotCloseWidget()));
}

void MainWidget::slotCloseWidget()
{
    this->close ();
}
