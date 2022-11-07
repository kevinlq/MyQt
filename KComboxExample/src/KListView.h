#pragma once

#include <QListView>

#include "KModel.h"
#include "KDelegate.h"
#include "KModel.h"

class KListView : public QListView
{
    Q_OBJECT
public:
    explicit KListView(QWidget *parent = nullptr);

    void loadModelData(const VTR_ModelData &data);

private:
    KModel *m_pModel = nullptr;
    KDelegate *m_pDelegate = nullptr;
};

