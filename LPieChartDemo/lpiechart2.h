#ifndef LPIECHART2_H
#define LPIECHART2_H

#include <QWidget>

struct PieItemDataPrivate;

class LPieChart2 : public QWidget
{
    Q_OBJECT
public:
    explicit LPieChart2(QWidget *parent = 0);
    ~LPieChart2();

    void setPieItems(const QString &name,const int &index);

    void setPieTotalNum();

private:
    void init();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QList<PieItemDataPrivate>m_itemList;
};

#endif // LPIECHART2_H
