#include "tracklistview.h"
#include "tracklistmodel.h"
#include "core/iradar.h"
#include "utils/fancyheaderview.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidget>
#include <QString>
#include <QAbstractItemModel>
using namespace RadarDisplay;

TrackListView::TrackListView(QWidget *parent) :
    QTableView(parent)
{
    setHorizontalHeader(new FancyHeaderView(Qt::Horizontal, this));
    horizontalHeader()->setSectionsMovable(true);
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

TrackListView::~TrackListView()
{
}

QSize TrackListView::sizeHint() const
{
    return QSize(340, 300);
}

