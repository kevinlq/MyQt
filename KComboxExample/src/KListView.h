#pragma once

#include <QListView>

class KListView : public QListView
{
    Q_OBJECT
public:
    explicit KListView(QWidget *parent = nullptr);
public Q_SLOTS:
    void onItemPressed(const QModelIndex &index);
};

