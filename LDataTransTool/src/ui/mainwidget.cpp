#include "mainwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include <QDebug>

#include "titleWidget/ltitlewidget.h"
#include "statusWidget/lstatuswidget.h"
#include "tooltWidget/ltoolwidget.h"

#include "formtrans.h"
#include "formdatabase.h"

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
    this->resize (840,640);

    //this->setWindowFlags(Qt::FramelessWindowHint);
    //setMouseTracking (true);
}

void MainWidget::initWidget()
{
    m_pTitleWidget = new LTitleWidget(this);
    m_pTitleWidget->setTitle ("数据采集模拟器");
    m_pTitleWidget->setTitleIcon (":/image/title.png");
    m_pToolWidget = new LToolWidget(this);

    m_pStatusWidget = new LStatusWidget(this);

    m_pStackedWidget = new QStackedWidget(this);

    m_pFrom = new FormTrans(this);
    m_pFormDatabase = new FormDatabase(this);

    m_pStackedWidget->addWidget (m_pFrom);
    m_pStackedWidget->addWidget(m_pFormDatabase);
    m_pStackedWidget->setCurrentIndex (0);

    m_pHCenLayout = new QHBoxLayout();
    m_pHCenLayout->addWidget (m_pToolWidget);
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

    connect (m_pToolWidget,SIGNAL(signalOnTbnClicked(QString)),
             this,SLOT(slotPageChange(QString)));

    connect(m_pFormDatabase,SIGNAL(signalSendDbFieldInfo(QString)),
            m_pFrom,SLOT(slotWriteSerial(QString)));
}

void MainWidget::slotCloseWidget()
{
    this->close ();
}

void MainWidget::slotPageChange(const QString &name)
{
    if (name == "数据转发"){
        m_pStackedWidget->setCurrentIndex(0);
    }else if (name == "数据库"){
        m_pStackedWidget->setCurrentIndex(1);
    }
}
