#include "CommonInc.h"

#include "KCombox.h"
#include "KModel.h"
#include "KListView.h"
#include "KDelegate.h"


KCombox::KCombox(QWidget *parent)
    : QComboBox(parent)
{
    m_pView = new KListView(this);
    m_pModel = new KModel(this);
    m_pDelegate = new KDelegate(this);

    this->setItemDelegate(m_pDelegate);
    this->setModel(m_pModel);
    this->setView(m_pView);

    // test data
    VTR_ModelData tmpData;
    for(int i = 0; i < 100; i++)
    {
        KModelData itemData;
        itemData.setKey(QString::number(i));
        itemData.setValue(QString("value%1").arg(i));

        for(int j = 0; j < 20; j++)
        {
            KModelData subItem;
            subItem.setKey(QString::number(i+j));
            subItem.setValue(QString("value%1%2").arg(i).arg(j));
            itemData.m_vtrChildData.push_back(subItem);
        }

        tmpData.push_back(itemData);
    }
    m_pModel->loadData(tmpData);
}

void KCombox::showPopup()
{
    QComboBox::showPopup();
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
