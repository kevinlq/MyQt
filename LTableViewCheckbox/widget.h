#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QModelIndex>

class TableModel;
class CheckBoxDelegate;

typedef struct FileRecord fileRecord;

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
    void updateCheckStatus();

    bool deleteRowItem();

private Q_SLOTS:
    void slotDateChange(const bool flag, const int row);

    void on_pbn_add_clicked();

    void on_pbnDelete_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Widget *ui;
    TableModel      *m_pMode;
    CheckBoxDelegate *m_pDelegate;

    QList<fileRecord> m_recordList;
    QList<int>m_rowList;
};

#endif // WIDGET_H
