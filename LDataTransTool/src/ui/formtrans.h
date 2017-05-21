#ifndef FORMTRANS_H
#define FORMTRANS_H

#include <QWidget>
#include <QTextStream>

class ReadSerialPort;
class QTimer;

namespace Ui {
class FormTrans;
}

class FormTrans : public QWidget
{
    Q_OBJECT

public:
    explicit FormTrans(QWidget *parent = 0);
    ~FormTrans();

private:
    void init();

    void initForm();

    void initWidget();

    void setSerialEnable(bool flag);

    void setTcpEnable(bool flag);

    void setUdpEnable(bool flag);

private slots:
    void slotReadSerial( const QByteArray &buff);

    void slotTimeOut();

    void on_tbn_send_clicked();

    void on_checkBox_serial_toggled(bool checked);

    void on_checkBox_tcp_toggled(bool checked);

    void on_checkBox_udp_toggled(bool checked);

    void on_tbnSerial_clicked();

    void on_tbn_find_clicked();

private:
    Ui::FormTrans *ui;

    ReadSerialPort  *m_pSerial;
    QString m_fileInfo;
    QTimer  *m_pTimer;
    bool m_fileIsOpen;
    QList <QByteArray> m_listByte;
};

#endif // FORMTRANS_H
