#pragma once

#include <QStyledItemDelegate>
#include <QObject>

class KDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit KDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const override;
};
