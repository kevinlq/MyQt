#include "separatorwidget.h"

using namespace RadarDisplay;

SeparatorWidget::SeparatorWidget(Qt::Orientation orient, QWidget *parent) :
    QFrame(parent)
{
    if (orient == Qt::Horizontal)
        setFrameShape(QFrame::HLine);
    else
        setFrameShape(QFrame::VLine);
    setFrameShadow(QFrame::Sunken);
}
