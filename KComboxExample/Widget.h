#pragma once

#include <QWidget>

class KCombox;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    KCombox *m_pComBox = nullptr;
};
