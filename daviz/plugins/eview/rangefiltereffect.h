#ifndef RANGEFILTEREFFECT_H
#define RANGEFILTEREFFECT_H

#include <qglshaderprogrameffect.h>
#include <QColor>

namespace RadarDisplay {
class RangeFilterEffect : public QGLShaderProgramEffect
{
public:
    RangeFilterEffect();
    void setColor(const QColor &color);
    void setRange(float start, float end);
};
}

#endif // RANGEFILTEREFFECT_H
