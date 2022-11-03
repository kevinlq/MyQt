#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>

class KListView;
class KModel;
class KDelegate;
class KCombox : public QComboBox
{
    Q_OBJECT
public:
    explicit KCombox(QWidget *parent = Q_NULLPTR);

    void showPopup() override;

private:
    KListView *m_pView = nullptr;
    KModel *m_pModel = nullptr;
    KDelegate *m_pDelegate = nullptr;
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

