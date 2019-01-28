#include "plotlistview.h"
#include "utils/fancyheaderview.h"

using namespace RadarDisplay;

PlotListView::PlotListView(QWidget *parent) :
    QTableView(parent)
{
    setHorizontalHeader(new FancyHeaderView(Qt::Horizontal, this));
    horizontalHeader()->setSectionsMovable(true);
//    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    verticalHeader()->hide();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QSize PlotListView::sizeHint() const
{
    return QSize(340, 300);
}
