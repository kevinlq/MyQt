#ifndef VIEWGROUP_H
#define VIEWGROUP_H

#include <QWidget>
#include <QList>

class QStackedLayout;
class QToolButton;
namespace RadarDisplay {
class IRadar;
class IView;
class ViewGroup : public QWidget
{
    Q_OBJECT
public:
    explicit ViewGroup(QWidget *parent = 0);
    void addView(IView *view);
    void removeView(IView *view);
    QList<IView *> viewList() const;

signals:

public slots:
    void setView(IView *view);
    
private:
    QStackedLayout *m_stackLayout;
    QList<IView *> m_views;
};
}

#endif // VIEWGROUP_H
