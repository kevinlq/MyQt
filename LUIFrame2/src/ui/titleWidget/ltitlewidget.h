#ifndef LTITLEWIDGET_H
#define LTITLEWIDGET_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QToolButton;
class QLabel;

class LToolWidget;

class LTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LTitleWidget(QWidget *parent = 0);
    ~LTitleWidget();

    void setTitleIcon(const QString &path);

    void setTitle(const QString &title);

private:
    void init();

    void initForm();

    void initWidget();

    void initConnect();

Q_SIGNALS:
    void signalClose();

private Q_SLOTS:

private:
    QWidget     *m_pwidgetBackground;
    QLabel      *m_plabelIcon;
    QLabel      *m_plabelTitle;
    QToolButton *m_pTbnClose;
    QHBoxLayout *m_pHToolLayout;

    LToolWidget *m_pToolWidget;

    QVBoxLayout *m_pVMainLayout;
};

#endif // LTITLEWIDGET_H
