#include "KPopViews.h"

KPopViews::KPopViews(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlags(this->windowFlags() | Qt::Popup);

    m_pMainLayout = new QHBoxLayout;
    m_pMainLayout->setContentsMargins(0,0,0,0);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->addStretch();
    setLayout(m_pMainLayout);

    m_vtrViews.clear();

    createView(0);
}

void KPopViews::showPopupView(const QSize &sz)
{
    m_defaultSize = sz;

    this->show();

    updateViewSize(0);
}

void KPopViews::loadModelData(const VTR_ModelData &modelData)
{
    if(modelData.isEmpty())
    {
        return;
    }

    m_vtrViews[0]->loadModelData(modelData);
}

KListView *KPopViews::createView(int nIndex)
{
    for(int i = 0; i < m_vtrViews.size(); i++)
    {
        if(m_vtrViews[i] && m_vtrViews[i]->property("index").toInt() == nIndex)
        {
            return m_vtrViews[i];
        }
    }

    auto pView = new(std::nothrow) KListView(this);
    pView->setProperty("index", nIndex);
    pView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(pView, &KListView::pressed, this, &KPopViews::onItemPressed);
    m_vtrViews.push_back(pView);

    m_pMainLayout->insertWidget(m_pMainLayout->count() - 1, pView);

    return pView;
}

void KPopViews::updateViewSize(int nCurIndex)
{
    int nVisibleCount = 0;
    for(int i = 0; i < m_vtrViews.size(); i++)
    {
        if(!m_vtrViews[i])
        {
            continue;
        }

        bool bVisible = true;

        if(i > nCurIndex)
        {
            bVisible = false;
        }

        m_vtrViews[i]->setVisible(bVisible);

        if( m_vtrViews[i]->isVisible())
        {
            nVisibleCount++;
            m_vtrViews[i]->resize(m_defaultSize);
        }
    }

    this->resize(nVisibleCount *m_defaultSize.width(), m_defaultSize.height());
}

void KPopViews::hideAllView()
{
    for(int i = 0; i < m_vtrViews.size(); i++)
    {
        if(m_vtrViews[i])
        {
            m_vtrViews[i]->setVisible(false);
        }
    }
    this->setVisible(false);
}

void KPopViews::onItemPressed(const QModelIndex &index)
{
    KListView *pView = qobject_cast<KListView*>(sender());

    if (!index.data().canConvert<void*>() || !pView)
    {
        return;
    }

    int nIndex = pView->property("index").toInt();

    KModelData *pModelData = (KModelData*)index.data().value<void*>();
    if(nullptr == pModelData)
    {
        return;
    }

    if(!pModelData->hasChild())
    {
        // not has child, hide all show views
        emit selectItemFinished(pModelData->value());
        hideAllView();
        return;
    }

    // find and create child view
    int nNextIndex = nIndex+1;
    KListView *pNextView = createView(nNextIndex);
    pNextView->loadModelData(pModelData->m_vtrChildData);

    updateViewSize(nNextIndex);
}

