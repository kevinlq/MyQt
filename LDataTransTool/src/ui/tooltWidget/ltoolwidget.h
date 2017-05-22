#ifndef LTOOLWIDGET_H
#define LTOOLWIDGET_H

#include <QWidget>

class QToolButton;
class QVBoxLayout;
class QSignalMapper;

class LToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LToolWidget(QWidget *parent = 0);
    ~LToolWidget();

private:
    void init();

    void initForm();

    void initWidget();

    void initConnect();

Q_SIGNALS:
    void signalOnTbnClicked(const QString &tbnText);

private Q_SLOTS:

private:
    QWidget         *m_pWidgetBack;
    QVBoxLayout     *m_pTbnLayout;
    QSignalMapper   *m_pSignalMap;
    QStringList     m_listTbnText;
    QToolButton     *m_pTbn;
    QVBoxLayout     *m_pVMainLayout;
};

#endif // LTOOLWIDGET_H
