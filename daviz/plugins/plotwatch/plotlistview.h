#ifndef PLOTLISTVIEW_H
#define PLOTLISTVIEW_H

#include "plotwatch_global.h"
#include <QTableView>
#include <QSize>

namespace RadarDisplay {
class PLOTWATCH_EXPORT PlotListView : public QTableView
{
    Q_OBJECT
public:
    explicit PlotListView(QWidget *parent = 0);
    QSize sizeHint() const;
signals:
    
public slots:
    
};
}
#endif // PLOTLISTVIEW_H
