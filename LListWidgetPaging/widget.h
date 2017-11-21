#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;

struct MyItem :public QWidget
{
    MyItem();
    ~MyItem();

private:
    QLabel *m_pLabelStr;
    QPushButton *m_pPbnChange;
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    QVector<MyItem *>m_vtrItem;

private slots:
    void on_pbnPre_clicked();

    void on_pbnNext_clicked();

private:
    Ui::Widget *ui;

    int m_nPageSize;      //每页记录数
    int m_nRecordCount;   //总记录数
    int m_nPageCount;     //总页数
};

#endif // WIDGET_H
