#include "Widget.h"
#include "src/KCombox.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto pHLayout = new QHBoxLayout;
    m_pComBox = new KCombox(this);
    m_pComBox->setMinimumSize(160, 28);
    pHLayout->addWidget(m_pComBox);

    pHLayout->addWidget(new KComboBox(this));

    pHLayout->addStretch();

    auto pMainLayout = new QVBoxLayout;
    pMainLayout->addLayout(pHLayout);
    pMainLayout->addStretch();
    setLayout(pMainLayout);

    this->resize(600, 480);
}

Widget::~Widget()
{
}

