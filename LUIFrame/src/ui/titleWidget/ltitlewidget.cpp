#include "ltitlewidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QStyle>

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
    m_plabelTitle->setObjectName ("label_title");
    m_plabelTitle->setText ("this is title");

    m_pTbnClose = new QToolButton(m_pwidgetBackground);
    m_pTbnClose->setObjectName ("tbn_close");
    m_pTbnClose->setAutoRaise (true);
    m_pTbnClose->setIcon (style ()->standardPixmap (QStyle::SP_TitleBarCloseButton));
    m_pTbnClose->setToolTip ("关闭");

    m_pHToolLayout = new QHBoxLayout(m_pwidgetBackground);
    m_pHToolLayout->addSpacing (2);
    m_pHToolLayout->addWidget (m_plabelIcon);
    m_pHToolLayout->addStretch (1);
    m_pHToolLayout->addWidget (m_plabelTitle);
    m_pHToolLayout->addStretch (10);
    m_pHToolLayout->addWidget (m_pTbnClose);
    m_pHToolLayout->addSpacing (2);

    m_pVMainLayout = new QVBoxLayout(this);
    m_pVMainLayout->addWidget (m_pwidgetBackground);
    m_pVMainLayout->setContentsMargins (0,0,0,0);

    setLayout (m_pVMainLayout);
}

void LTitleWidget::initConnect()
{
    connect (m_pTbnClose,SIGNAL(clicked(bool)),this,SIGNAL(signalClose()));
}
