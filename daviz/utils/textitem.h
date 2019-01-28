#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "utils_global.h"
#include <QGraphicsSimpleTextItem>
#include <QColor>

namespace RadarDisplay {
class UTILS_EXPORT TextItem : public QGraphicsSimpleTextItem
{
public:
    TextItem(QGraphicsItem *parent = 0);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QColor m_backgroundColor;
};
}
#endif // TEXTITEM_H
