#ifndef FORMDATABASE_H
#define FORMDATABASE_H

#include <QWidget>

namespace Ui {
class FormDatabase;
}

class FormDatabase : public QWidget
{
    Q_OBJECT

public:
    explicit FormDatabase(QWidget *parent = 0);
    ~FormDatabase();

private:
    void init();

    QString getFileInfo();

    void showSqliteInfo();

Q_SIGNALS:

private Q_SLOTS:

    void on_pbn_openDb_clicked();

    void on_comboBox_tableName_currentIndexChanged(const QString &arg1);

    void on_radioButton_mysql_toggled(bool checked);

protected:
    virtual bool eventFilter(QObject *, QEvent *);

private:
    Ui::FormDatabase *ui;

    QString m_file;
};

#endif // FORMDATABASE_H
