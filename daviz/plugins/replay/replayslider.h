#ifndef REPLAYSLIDER_H
#define REPLAYSLIDER_H

#include <QSlider>
#include <QProxyStyle>

namespace RadarDisplay {
class ReplaySlider : public QSlider
{
    Q_OBJECT
public:
    explicit ReplaySlider(Qt::Orientation orient, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

namespace Internal {
class ReplaySliderStyle : public QProxyStyle
{
    Q_OBJECT
public:
    ReplaySliderStyle(QStyle *style);
    int styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const;
};
}
}
#endif // REPLAYSLIDER_H
