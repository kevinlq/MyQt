#include "CommonInc.h"

#include "KDelegate.h"
#include "KModel.h"


KDelegate::KDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void KDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
    {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, viewOption, index);

    if (!index.data().canConvert<void*>())
    {
        qDebug() << "fail." << index;
        return;
    }

    KModelData *pModelData = (KModelData*)index.data().value<void*>();
    if(nullptr == pModelData)
    {
        return;
    }

    painter->drawText(option.rect, Qt::AlignHCenter | Qt::AlignVCenter, pModelData->value());
}

QSize KDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return QSize(100, 30);
}
