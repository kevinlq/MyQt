#include "CommonInc.h"

#include "KModel.h"

KModelData::KModelData()
{
    //qDebug() << "constructor KModelData";
}

KModelData::~KModelData()
{
    //qDebug() << "~destructor KModelData";
}

KModelData::KModelData(const KModelData &other)
{
    this->m_key             = other.m_key;
    this->m_value           = other.m_value;
    this->m_vtrChildData    = other.m_vtrChildData;
}

KModelData &KModelData::operator =(const KModelData &other)
{
    if (this != &other)
    {
        this->m_key             = other.m_key;
        this->m_value           = other.m_value;
        this->m_vtrChildData    = other.m_vtrChildData;
    }

    return *this;
}

bool KModelData::hasChild() const
{
    return m_vtrChildData.count() > 0;
}

const QString &KModelData::key() const
{
    return m_key;
}

void KModelData::setKey(const QString &newKey)
{
    m_key = newKey;
}

const QString &KModelData::value() const
{
    return m_value;
}

void KModelData::setValue(const QString &newValue)
{
    m_value = newValue;
}

KModel::KModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

void KModel::loadData(const VTR_ModelData &listData)
{
    m_vtrModelData = listData;

    beginResetModel();
    endResetModel();
}

int KModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return m_vtrModelData.count();
}

int KModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant KModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int nRow = index.row();
        if (nRow >= 0 && nRow < m_vtrModelData.count())
        {
            return QVariant::fromValue((void*)&m_vtrModelData[nRow]);
        }
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    return QVariant();
}

bool KModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    int nColumn = index.column();

    KModelData *pData = &m_vtrModelData[index.row()];

    switch (role)
    {
    case Qt::DisplayRole:
    {
        pData->setValue(value.toString());
        emit dataChanged(index, index);
        return true;
    }
    default:
        return false;
    }

    return false;
}

Qt::ItemFlags KModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return flags;
}


