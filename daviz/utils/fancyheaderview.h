#ifndef FANCYHEADERVIEW_H
#define FANCYHEADERVIEW_H

#include "utils_global.h"
#include <QHeaderView>

class QAction;
namespace RadarDisplay {
class UTILS_EXPORT FancyHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit FancyHeaderView(Qt::Orientation orient, QWidget *parent = 0);
    void contextMenuEvent(QContextMenuEvent *event);
    
signals:
    void sectionAboutToBeHidden(int index, Qt::Orientation orientation);
    void sectionAboutToBeShown(int index, Qt::Orientation orientation);
    void sectionHidden(int index, Qt::Orientation orientation);
    void sectionShown(int index, Qt::Orientation orientation);

private:
    QAction *m_resizeAction;
    QAction *m_autoResizeAction;
};
}
#endif // FANCYHEADERVIEW_H
