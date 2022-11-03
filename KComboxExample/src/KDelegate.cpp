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

    QVariant v = index.data();
    if (!v.canConvert<KModelData>())
    {
        qDebug() << "fail." << index;
        return;
    }

    KModelData pModelData = (v.value<KModelData>());

    qDebug() << pModelData.key() << pModelData.value() << this << index;

    painter->drawText(option.rect, pModelData.value());
}

QSize KDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return QSize(100, 30);
}
