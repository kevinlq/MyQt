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

    void setData(QVector<double> value,QVector<QColor> colors,
                 QVector<QString> names);

private:
    void init();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QVector<double> m_qvValues;
    QVector<QColor> m_qvColors;
    QVector<QString>m_qvName;
};

#endif // LPIECHART2_H
