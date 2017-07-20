#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class SerialPortObj;
class QTimer;

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
    void init();

    void initForm();

    void initObj();

Q_SIGNALS:

private Q_SLOTS:

    void slotReceSerial(const QByteArray &buf);

    void slotUpdateTime();

    void slotAutoSendInfo();

    void on_btnOpen_clicked();

    void on_btnSend_clicked();

    void on_pbn_clearRece_clicked();

    void on_pbn_clearSend_clicked();

    void on_chFileSend_clicked(bool checked);

    void on_cboxTime_activated(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    void setSerialConEnable(const bool&flag);

    void setSendAreaEnable(const bool &flag);

    void setShowText(const QString &txt);

    void setShowText(const QByteArray &txt);

private:
    Ui::Widget *ui;
    SerialPortObj   *m_pSerialObj;
    QTimer  *m_pUpdateTime;
    QTimer  *m_pAutoSendTime;
    QStringList m_fileConList;

    int m_sendCount;
    int m_receCount;
};

#endif // WIDGET_H
