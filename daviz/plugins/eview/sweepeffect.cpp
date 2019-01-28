#include "sweepeffect.h"
#if QT_VERSION >= 0x050000
#include <QOpenGLShaderProgram>
#else
#include <QGLShaderProgram>
#endif

#include <QDebug>

using namespace RadarDisplay;

SweepEffect::SweepEffect() :
    QGLShaderProgramEffect()
{
    setVertexShaderFromFile(":/shaders/sweepeffect.vert");
    setFragmentShaderFromFile(":/shaders/sweepeffect.frag");
}

void SweepEffect::setAntennaPosition(float degree)
{
    program()->setUniformValue("antennaPosition", degree);
}
