#ifndef SWEEPEFFECT_H
#define SWEEPEFFECT_H

#include <qglshaderprogrameffect.h>
#include <QColor>

namespace RadarDisplay {
class SweepEffect : public QGLShaderProgramEffect
{
public:
    SweepEffect();
    void setAntennaPosition(float degree);
};
}

#endif // SWEEPEFFECT_H
