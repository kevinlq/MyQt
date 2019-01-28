#include "ppieffect.h"
#if QT_VERSION >= 0x050000
#include <QOpenGLShaderProgram>
#else
#include <QGLShaderProgram>
#endif

#include <QDebug>

using namespace RadarDisplay;

PPIEffect::PPIEffect() :
    QGLShaderProgramEffect()
{
    setVertexShaderFromFile(":/shaders/ppieffect.vert");
    setFragmentShaderFromFile(":/shaders/ppieffect.frag");
}

void PPIEffect::setColor(const QColor &color)
{
    program()->setUniformValue("baseColor", color);
}

void PPIEffect::setAntennaPosition(float degree)
{
    program()->setUniformValue("antennaPosition", degree);
}

void PPIEffect::setElevationRange(float start, float end)
{
    program()->setUniformValue("elevStart", start);
    program()->setUniformValue("elevEnd", end);
}
