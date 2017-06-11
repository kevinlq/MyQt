#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>


class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CheckBoxDelegate(QObject *parent = 0);
    ~CheckBoxDelegate();

    /**
     *@brief 重载绘制函数
     * 绘制复选框
    */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    //响应鼠标事件，更新数据
    bool editorEvent (QEvent *event, QAbstractItemModel *model,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index);

Q_SIGNALS:
    void signalCheckChange(const bool,const int row);

};

#endif // CHECKBOXDELEGATE_H
