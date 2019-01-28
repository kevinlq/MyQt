#ifndef SELECTIONITEM_H
#define SELECTIONITEM_H

#include "utils_global.h"
#include <QGraphicsPathItem>

namespace RadarDisplay {
class UTILS_EXPORT SelectionItem : public QGraphicsPathItem
{
public:
    SelectionItem(QGraphicsItem *parent = 0);
};
}
#endif // SELECTIONITEM_H
