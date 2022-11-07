#include "CommonInc.h"

#include "KCombox.h"

KCombox::KCombox(QWidget *parent)
    : QComboBox(parent)
{
    m_pViewPtr = new KPopViews(this);
    m_pViewPtr->setVisible(false);

    connect(m_pViewPtr, &KPopViews::selectItemFinished,
            [this](const QVariant &v){
        this->clear();
        this->addItem(v.toString());
    });
}

void KCombox::setModelData(const VTR_ModelData &data)
{
    m_pViewPtr->loadModelData(data);
}

void KCombox::showPopup()
{
    //QComboBox::showPopup();

    QPoint pt = this->mapToGlobal(QPoint{0,0});

    m_pViewPtr->move(pt.x(), pt.y() + this->height());

    m_pViewPtr->showPopupView(QSize(this->width(), 240));
}

KComboBox::KComboBox(QWidget *parent)
    : QWidget(parent)
{
    m_pBoxEdit = new QLineEdit(this);
    m_pBoxButton = new QPushButton(this);
    m_pBoxButton->setCheckable(true);
    m_pBoxButton->setFocusPolicy(Qt::NoFocus);
    m_pBoxButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pBoxButton->setMaximumSize(20,22);

    auto pHLayout = new QHBoxLayout(this);
    pHLayout->setMargin(1);
    pHLayout->setSpacing(1);
    pHLayout->addWidget(m_pBoxEdit);
    pHLayout->addWidget(m_pBoxButton);
}
