#ifndef LSTATUSWIDGET_H
#define LSTATUSWIDGET_H

#include <QWidget>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class LStatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LStatusWidget(QWidget *parent = 0);
    ~LStatusWidget();

private:
    void init();

    void initForm();

    void initWidget();

    void initConnect();

Q_SIGNALS:

private Q_SLOTS:

private:
    QWidget         *m_pwidgetBack;
    QHBoxLayout     *m_pHLayout;
    QLabel          *m_plabelInfo;
    QVBoxLayout     *m_pVMainLayout;
};

#endif // LSTATUSWIDGET_H
