#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>

#include "KPopViews.h"

class KCombox : public QComboBox
{
    Q_OBJECT
public:
    explicit KCombox(QWidget *parent = Q_NULLPTR);

    void setModelData(const VTR_ModelData &data);

    void showPopup() override;

private:
    KPopViews   *m_pViewPtr = nullptr;
};

class KComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit KComboBox(QWidget *parent = nullptr);

private:
    QLineEdit   *m_pBoxEdit = nullptr;
    QPushButton *m_pBoxButton = nullptr;
};

