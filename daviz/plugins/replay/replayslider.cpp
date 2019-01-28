#include "replayslider.h"
using namespace RadarDisplay;
using namespace RadarDisplay::Internal;

ReplaySlider::ReplaySlider(Qt::Orientation orient, QWidget *parent) :
    QSlider(orient, parent)
{
    setStyle(new ReplaySliderStyle(style()));
}


ReplaySliderStyle::ReplaySliderStyle(QStyle *style) :
    QProxyStyle(style)
{
}

int ReplaySliderStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
        return Qt::LeftButton;
    return baseStyle()->styleHint(hint, option, widget, returnData);
}
