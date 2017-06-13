#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "customWidget/nbasemoveablewidget.h"

class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;

class LTitleWidget;
class LStatusWidget;
class LToolWidget;

class FormTrans;
class FormDatabase;

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

    void slotPageChange(const QString &name);

private:
    LTitleWidget    *m_pTitleWidget;
    LStatusWidget   *m_pStatusWidget;
    LToolWidget     *m_pToolWidget;
    QStackedWidget  *m_pStackedWidget;
    FormTrans       *m_pFrom;
    FormDatabase    *m_pFormDatabase;

    QHBoxLayout     *m_pHCenLayout;

    QVBoxLayout     *m_pVMainLayout;
};

#endif // MAINWIDGET_H
