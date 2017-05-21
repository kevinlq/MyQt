#include "lstatuswidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>

LStatusWidget::LStatusWidget(QWidget *parent)
    : QWidget(parent)
{   
    init ();
}

LStatusWidget::~LStatusWidget()
{
#if DEBUG_OUT
    qDebug ()<<"destroy statusWidget!";
#endif
}

void LStatusWidget::init()
{
    initForm ();

    initWidget ();

    initConnect ();
}

void LStatusWidget::initForm()
{
    setFixedHeight (40);
}

void LStatusWidget::initWidget()
{
    m_pwidgetBack = new QWidget(this);
    m_pwidgetBack->setObjectName ("widget_status");

    m_pHLayout = new QHBoxLayout(m_pwidgetBack);

    m_plabelInfo = new QLabel(m_pwidgetBack);
    m_plabelInfo->setObjectName ("label_white");
    m_plabelInfo->setText ("this is status");

    m_pHLayout->addSpacing (2);
    m_pHLayout->addWidget (m_plabelInfo);
    m_pHLayout->addStretch ();

    m_pVMainLayout = new QVBoxLayout(this);
    m_pVMainLayout->addWidget (m_pwidgetBack);
    m_pVMainLayout->setContentsMargins (0,0,0,0);

    setLayout (m_pVMainLayout);
}

void LStatusWidget::initConnect()
{
    //
}
