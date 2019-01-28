#ifndef TRACKLISTVIEW_H
#define TRACKLISTVIEW_H

#include "tracklistview_global.h"
#include "core/icore.h"
#include <qglobal.h>
#include <QWidget>
#include <QTableView>

namespace RadarDisplay {
class IRadar;
class TrackListModel;
class TRACKLISTVIEW_EXPORT TrackListView : public QTableView
{
    Q_OBJECT
public:
    explicit TrackListView(QWidget *parent = 0);
    ~TrackListView();
    QSize sizeHint() const;

private:
    IRadar *m_radar;
};
}

#endif // TRACKLISTVIEW_H
