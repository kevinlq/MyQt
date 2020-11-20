#ifndef LAYOUTSELECTPANEL_H
#define LAYOUTSELECTPANEL_H

#include <QWidget>

class LayoutSelectPanelPrivate;

namespace QfwUtil{

class LayoutSelectPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LayoutSelectPanel(QWidget *parent = nullptr);
    ~LayoutSelectPanel();

    // 设置面板当前布局行列
    void setPanelLayout(int nRow, int nColumn );

protected:
    virtual void leaveEvent(QEvent *event);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

signals:
    // 当鼠标点击选择布局后触发该信号
    void signalSelectLayoutChange(int nRow, int nColumn);

private:
    LayoutSelectPanelPrivate* m_pPanelImpl;
};

} // namespace QfwUtil

#endif // LAYOUTSELECTPANEL_H
