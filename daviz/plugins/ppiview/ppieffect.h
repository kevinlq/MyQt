#ifndef PPIEFFECT_H
#define PPIEFFECT_H

#include <qglshaderprogrameffect.h>
#include <QColor>

namespace RadarDisplay {
class PPIEffect : public QGLShaderProgramEffect
{
public:
    PPIEffect();
    void setColor(const QColor &color);
    void setAntennaPosition(float degree);
    void setElevationRange(float start, float end);
};
}

#endif // PPIEFFECT_H
