#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include "gdatadef.h"


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = 0);
    ~TableModel();

    //更新表格数据
    void updateData(QList<FileRecord >recordList);

    //模型行数
    int rowCount (const QModelIndex &parent) const;

    //模型列数
    int columnCount (const QModelIndex &parent) const;

    //设置表格数据
    bool setData (const QModelIndex &index, const QVariant &value, int role);

    //表格项数据
    QVariant data (const QModelIndex &index, int role) const;

    //表头数据
    QVariant headerData (int section, Qt::Orientation orientation, int role) const;

    //设置表格是否可选中
    Qt::ItemFlags flags (const QModelIndex &index) const;

private:
    QList<fileRecord >m_recordList;
};

#endif // TABLEMODEL_H
