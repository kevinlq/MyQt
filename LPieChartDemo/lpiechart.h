#ifndef LPIECHART_H
#define LPIECHART_H

#include <QWidget>

class LPieChart : public QWidget
{
    Q_OBJECT
public:
    explicit LPieChart(QWidget *parent = 0);
    ~LPieChart();

private:
    void init();

protected:
    void paintEvent(QPaintEvent *ev);

Q_SIGNALS:

private Q_SLOTS:

private:
};

#endif // LPIECHART_H
