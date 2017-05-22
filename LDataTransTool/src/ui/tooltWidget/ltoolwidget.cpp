#include "ltoolwidget.h"

#include <QDebug>
#include <QToolButton>
#include <QVBoxLayout>
#include <QSignalMapper>

#include <QLineEdit>

LToolWidget::LToolWidget(QWidget *parent)
    : QWidget(parent)
{
    init ();
}

LToolWidget::~LToolWidget()
{
#if DEBUG_OUT
    qDebug ()<<"destroy toolWidget";
#endif
}

void LToolWidget::init()
{
    initForm ();

    initWidget ();

    initConnect ();
}

void LToolWidget::initForm()
{
    this->setFixedWidth (120);

    setFocusPolicy (Qt::ClickFocus);
}

void LToolWidget::initWidget()
{
    m_pWidgetBack = new QWidget(this);
    m_pWidgetBack->setObjectName ("tool_widget");

    m_pTbnLayout = new QVBoxLayout(m_pWidgetBack);

    m_pSignalMap = new QSignalMapper(this);

    m_listTbnText <<"数据转发";

    foreach (QString text, m_listTbnText) {
        m_pTbn = new QToolButton(m_pWidgetBack);
        m_pTbn->setText (text);
        m_pTbn->setMinimumSize (100,30);
        m_pTbn->setAutoRaise (true);
        m_pTbnLayout->addWidget (m_pTbn);
        m_pSignalMap->setMapping (m_pTbn,text);
        connect (m_pTbn,SIGNAL(clicked(bool)),m_pSignalMap,SLOT(map()));
    }
    connect (m_pSignalMap,SIGNAL(mapped(QString)),this,SIGNAL(signalOnTbnClicked(QString)));

    m_pTbnLayout->addStretch ();
    m_pTbnLayout->setContentsMargins (6,0,2,2);

    m_pVMainLayout = new QVBoxLayout(this);
    m_pVMainLayout->addWidget (m_pWidgetBack);
    m_pVMainLayout->setContentsMargins (0,0,0,0);
    setLayout (m_pVMainLayout);
}

void LToolWidget::initConnect()
{
    //
}
