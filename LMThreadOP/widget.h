#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTimer;
class WorkDaataThread;
class MessageQueue;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pbnStart_clicked();

    void slotTimeOut();

    void slotRMsg(const QString &msg);

private:
    Ui::Widget *ui;

    QTimer          *m_pTimer;
    MessageQueue    *m_pMessageQueue;
    WorkDaataThread *m_pWorkThread;
};

#endif // WIDGET_H
