#include "tablemodel.h"
#include <QColor>

TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

TableModel::~TableModel()
{
}

void TableModel::updateData(QList<FileRecord> recordList)
{
    m_recordList = recordList;
    beginResetModel ();
    endResetModel ();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_recordList.count ();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return COLUMN_COUNT;
}

bool TableModel::setData(const QModelIndex &index,
                         const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int nColumn = index.column();
    FileRecord record = m_recordList.at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
    {
        if (nColumn == File_PATH_COLUMN)
        {
            record.strFilePath = value.toString();

            m_recordList.replace(index.row(), record);
            emit dataChanged(index, index);
            return true;
        }else if (nColumn == File_SIZE_COLUMN)
        {
            record.strFileSize = value.toString ();
            m_recordList.replace (index.row (),record);
            emit dataChanged (index,index);
            return true;
        }else if (nColumn == File_SPEED_COLUMN)
        {
            record.strSpeed = value.toString ();
            m_recordList.replace (index.row (),record);
            emit dataChanged (index,index);
            return true;
        }
    }
    case Qt::CheckStateRole:
    case Qt::UserRole:
    {
        if (nColumn == CHECK_BOX_COLUMN)
        {
            record.bChecked = value.toBool();

            m_recordList.replace(index.row(), record);
            emit dataChanged(index, index);
            return true;
        }
    }
    default:
        return false;
    }
    return false;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int nRow = index.row();
    int nColumn = index.column();
    FileRecord record = m_recordList.at(nRow);

    switch (role)
    {
    case Qt::TextColorRole:
        return QColor(0,0,0);
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::DisplayRole:
    {
        if (nColumn == File_PATH_COLUMN)
            return record.strFilePath;
        else if (nColumn == File_SIZE_COLUMN)
            return record.strFileSize;
        else if (nColumn == File_SPEED_COLUMN)
            return record.strSpeed;
        return "";
    }
    case Qt::UserRole:
    {
        if (nColumn == CHECK_BOX_COLUMN)
            return record.bChecked;
    }
    default:
        return QVariant();
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
    case Qt::DisplayRole:
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == CHECK_BOX_COLUMN)
                return QString("status");

            if (section == File_PATH_COLUMN)
                return QString("path");

            if (section == File_SIZE_COLUMN)
                return QString("size");

            if (section == File_SPEED_COLUMN)
                return QString("speed");
        }
    }
    default:
        return QVariant();
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return flags;
}
