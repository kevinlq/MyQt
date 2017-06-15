#ifndef FORMDATABASE_H
#define FORMDATABASE_H

#include <QWidget>

class ReadFieldObj;
class QThread;

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
    void signalSendDbFieldInfo(const QString &txt);

private Q_SLOTS:

    void on_pbn_openDb_clicked();

    void on_comboBox_tableName_currentIndexChanged(const QString &arg1);

    void on_radioButton_mysql_toggled(bool checked);

    void on_pbn_read_clicked();

    void on_comboBox_tableField_currentIndexChanged(const QString &arg1);

protected:
    virtual bool eventFilter(QObject *, QEvent *);

private:
    Ui::FormDatabase *ui;

    QString m_file;
    ReadFieldObj    *m_preadObj;
    QThread         *m_preadThread;
};

#endif // FORMDATABASE_H
