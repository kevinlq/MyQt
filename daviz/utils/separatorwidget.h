#ifndef SEPARATORWIDGET_H
#define SEPARATORWIDGET_H

#include "utils_global.h"
#include <QFrame>

namespace RadarDisplay {
class UTILS_EXPORT SeparatorWidget : public QFrame
{
    Q_OBJECT
public:
    explicit SeparatorWidget(Qt::Orientation orient, QWidget *parent = 0);
    
signals:
    
public slots:
    
};
}
#endif // SEPARATORWIDGET_H
