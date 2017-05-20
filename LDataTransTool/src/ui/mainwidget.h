#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "nbasemoveablewidget.h"

class QStackedWidget;
class QVBoxLayout;

class LTitleWidget;
class LStatusWidget;

class MainWidget : public NBaseMoveableWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
private:
    void init();

    void initForm();

    void initWidget();

    void initConnect();

Q_SIGNALS:

private Q_SLOTS:
    void slotCloseWidget();

private:
    LTitleWidget    *m_pTitleWidget;
    LStatusWidget   *m_pStatusWidget;
    QStackedWidget  *m_pStackedWidget;

    QVBoxLayout     *m_pVMainLayout;
};

#endif // MAINWIDGET_H
