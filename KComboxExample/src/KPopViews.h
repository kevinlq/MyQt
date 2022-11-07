#pragma once

#include <QWidget>
#include "CommonInc.h"
#include "KListView.h"

class KPopViews : public QWidget
{
    Q_OBJECT
public:
    explicit KPopViews(QWidget *parent = nullptr);

    void showPopupView(const QSize &sz);

    void loadModelData(const VTR_ModelData &modelData);

private:
    KListView *createView(int nIndex);
    void updateViewSize(int nCurIndex);
    void hideAllView();

Q_SIGNALS:
    void selectItemFinished(const QVariant &selectData);
public Q_SLOTS:
    void onItemPressed(const QModelIndex &index);
private:
    QHBoxLayout *m_pMainLayout = nullptr;
    int m_nViewWidth = 100;
    QSize m_defaultSize = QSize(100, 240);
    QVector<KListView*> m_vtrViews;
};

