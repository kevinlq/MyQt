#include "CommonInc.h"

#include "KListView.h"


KListView::KListView(QWidget *parent)
    : QListView(parent)
{
    m_pModel = new KModel(this);
    m_pDelegate = new KDelegate(this);

    this->setModel(m_pModel);
    this->setItemDelegateForColumn(0, m_pDelegate);
}

void KListView::loadModelData(const VTR_ModelData &data)
{
    m_pModel->loadData(data);
}
