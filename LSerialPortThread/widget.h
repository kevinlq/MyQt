#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class SerialPortObj;
class QThread;

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
    Ui::Widget *ui;

    SerialPortObj   *m_pserialObj;
    QThread         *m_pThread;
};

#endif // WIDGET_H
