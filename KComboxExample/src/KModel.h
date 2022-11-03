#pragma once

#include <QAbstractListModel>
#include <QAbstractItemDelegate>
#include <QVector>

class KModelData
{
public:
    explicit KModelData();
    ~KModelData();
    KModelData(const KModelData &other);
    KModelData& operator =(const KModelData &other);

    bool hasChild() const;

    const QString &key() const;
    void setKey(const QString &newKey);

    const QString &value() const;
    void setValue(const QString &newValue);
private:
    QString m_key;
    QString m_value;
public:
    QVector<KModelData> m_vtrChildData;
};
Q_DECLARE_METATYPE(KModelData)

using VTR_ModelData = QVector<KModelData>;

class KModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit KModel(QObject *parent = nullptr);

    void loadData(const VTR_ModelData &listData);

    int rowCount(const QModelIndex &index)const  override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    VTR_ModelData m_vtrModelData;
};

