#include "checkboxdelegate.h"

#include "tablemodel.h"

#include <QCheckBox>
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

CheckBoxDelegate::~CheckBoxDelegate()
{
}

void CheckBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    //绘制按钮所需的参数
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    QStyledItemDelegate::paint(painter, viewOption, index);

    //如果是checkbox列
    if (index.column() == CHECK_BOX_COLUMN)
    {
        ///获取当前项值
        bool data = index.model()->data(index, Qt::UserRole).toBool();

        ///获取项风格设置
        QStyleOptionButton checkBoxStyle;
        checkBoxStyle.state = data ? QStyle::State_On : QStyle::State_Off;
        checkBoxStyle.state |= QStyle::State_Enabled;
        checkBoxStyle.iconSize = QSize(30, 30);
        checkBoxStyle.rect = option.rect;

        QCheckBox checkBox;
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox,
                                             &checkBoxStyle, painter, &checkBox);
    }else{
        ///否则调用默认的委托
        QStyledItemDelegate::paint (painter,option,index);
    }
}

bool CheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
    QRect decorationRect = option.rect;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress &&
            decorationRect.contains(mouseEvent->pos()))
    {
        //如果是checkbox列
        if (index.column() == CHECK_BOX_COLUMN)
        {
            bool data = model->data(index, Qt::UserRole).toBool();

            model->setData(index, !data, Qt::UserRole);

            //当复选框状态改变时，发射信号出去，通知外部
            //这里当复选框选中时,data为false，所以为了和正常逻辑统一，取反
            emit signalCheckChange (!data,index.row ());
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
