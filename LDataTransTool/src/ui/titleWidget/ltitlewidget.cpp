#include "ltitlewidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QStyle>

#define TITLE_STYLE "QWidget#title_widet{\
background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #81AACA,stop:1 #2A89D6);}\
QToolButton#tbn_close{\
    border-radius:1px;\
color:#386487;\
padding:3px;\
    background-color:rgba(255,255,255,80);\
    border-style:none;}\
QToolButton#tbn_close:hover{\
                          color:#FFFFFF;\
background-color:rgba(112,66,223,50);}\
QToolButton#tbn_close:pressed{\
background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #DEF0FE,stop:1 #C0DEF6);}"

LTitleWidget::LTitleWidget(QWidget *parent)
    : QWidget(parent)
{
    init ();
}

LTitleWidget::~LTitleWidget()
{
#if DEBUG_OUT
    qDebug ()<<"destroy titleWidget!";
#endif
}

void LTitleWidget::setTitleIcon(const QString &path)
{
    Q_ASSERT(path != "");
    m_plabelIcon->setPixmap (QPixmap(path));
}

void LTitleWidget::setTitle(const QString &title)
{
    Q_ASSERT(title != "");
    m_plabelTitle->setText (title);
}

void LTitleWidget::init()
{
    initForm ();
}

void LTitleWidget::initForm()
{
    setFixedHeight (60);

    initWidget ();

    initConnect ();
}

void LTitleWidget::initWidget()
{
    m_pwidgetBackground = new QWidget(this);
    m_pwidgetBackground->setObjectName ("title_widet");

    m_plabelIcon = new QLabel(m_pwidgetBackground);

    m_plabelTitle = new QLabel(m_pwidgetBackground);
    m_plabelTitle->setText ("this is title");

    m_pTbnClose = new QToolButton(m_pwidgetBackground);
    m_pTbnClose->setObjectName ("tbn_close");
    m_pTbnClose->setAutoRaise (true);
    m_pTbnClose->setIcon (style ()->standardPixmap (QStyle::SP_TitleBarCloseButton));
    m_pTbnClose->setToolTip ("关闭");

    m_pHToolLayout = new QHBoxLayout(m_pwidgetBackground);
    m_pHToolLayout->addSpacing (2);
    m_pHToolLayout->addWidget (m_plabelIcon);
    m_pHToolLayout->addSpacing (4);
    m_pHToolLayout->addWidget (m_plabelTitle);
    m_pHToolLayout->addStretch ();
    m_pHToolLayout->addWidget (m_pTbnClose);
    m_pHToolLayout->addSpacing (2);

    m_pVMainLayout = new QVBoxLayout(this);
    m_pVMainLayout->addWidget (m_pwidgetBackground);
    m_pVMainLayout->setContentsMargins (0,0,0,0);

    setLayout (m_pVMainLayout);

    setStyleSheet (TITLE_STYLE);
}

void LTitleWidget::initConnect()
{
    connect (m_pTbnClose,SIGNAL(clicked(bool)),this,SIGNAL(signalClose()));
}
