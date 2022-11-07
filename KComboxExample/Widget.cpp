#include "Widget.h"
#include "src/KCombox.h"

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

    // test data
    VTR_ModelData tmpData;
    for(int i = 0; i < 20; i++)
    {
        KModelData itemData;
        itemData.setKey(QString::number(i));
        itemData.setValue(QString("level 0 value:%1").arg(i));

        for(int j = 0; j < 22; j++)
        {
            KModelData subItem1;
            subItem1.setKey(QString::number(i+j));
            subItem1.setValue(QString("levle1 value:%1%2").arg(i).arg(j));

            for(int m = 0; m < 13; m++)
            {
                KModelData subItem2;
                subItem2.setKey(QString::number(i+j+m));
                subItem2.setValue(QString("levle2 value:%1%2%3").arg(i).arg(j).arg(m));

                for(int n = 0; n < 14; n++)
                {
                    KModelData subItem3;
                    subItem3.setKey(QString::number(i+j+m));
                    subItem3.setValue(QString("levle3 value:%1%2%3%4").arg(i).arg(j).arg(m).arg(n));
                    subItem2.m_vtrChildData.push_back(subItem3);
                }

                subItem1.m_vtrChildData.push_back(subItem2);
            }
            itemData.m_vtrChildData.push_back(subItem1);
        }

        tmpData.push_back(itemData);
    }

    m_pComBox->setModelData(tmpData);
}

Widget::~Widget()
{
}

