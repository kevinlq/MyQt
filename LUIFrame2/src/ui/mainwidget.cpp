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
}

void MainWidget::initWidget()
{
    m_pTitleWidget = new LTitleWidget(this);
    m_pTitleWidget->setTitleIcon (":/image/title.png");
    m_pTitleWidget->setTitle ("XXX管理系统");

    m_pStatusWidget = new LStatusWidget(this);

    m_pStackedWidget = new QStackedWidget(this);

    m_pHCenLayout = new QHBoxLayout();
    m_pHCenLayout->addWidget (m_pStackedWidget);
    m_pHCenLayout->setSpacing (0);
    m_pHCenLayout->setContentsMargins (0,0,0,0);

    m_pVMainLayout = new QVBoxLayout(this);
    m_pVMainLayout->addWidget (m_pTitleWidget);
    m_pVMainLayout->addLayout (m_pHCenLayout);
    m_pVMainLayout->addWidget (m_pStatusWidget);
    m_pVMainLayout->setSpacing (0);
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

void MainWidget::slotPageChange(const QString &name)
{
    qDebug ()<<name;
}
