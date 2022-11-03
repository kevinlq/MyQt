#include "CommonInc.h"

#include "KListView.h"
#include "KModel.h"

KListView::KListView(QWidget *parent)
    : QListView(parent)
{
    connect(this, &KListView::pressed,
            this, &KListView::onItemPressed);
}

void KListView::onItemPressed(const QModelIndex &index)
{
    KModel *pModel = qobject_cast<KModel*>(this->model());

    QVariant v = pModel->data(index, Qt::DisplayRole);
    if (!v.canConvert<KModelData>())
    {
        return;
    }

    KModelData pModelData = (v.value<KModelData>());

    qDebug() << "KListView:"<<  pModelData.value() << index;
}
