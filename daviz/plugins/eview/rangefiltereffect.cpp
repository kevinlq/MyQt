#include "rangefiltereffect.h"
#if QT_VERSION >= 0x050000
#include <QOpenGLShaderProgram>
#else
#include <QGLShaderProgram>
#endif

#include <QDebug>

using namespace RadarDisplay;

RangeFilterEffect::RangeFilterEffect() :
    QGLShaderProgramEffect()
{
    setVertexShaderFromFile(":/shaders/rangefilter.vert");
    setFragmentShaderFromFile(":/shaders/rangefilter.frag");
}

void RangeFilterEffect::setColor(const QColor &color)
{
    program()->setUniformValue("baseColor", color);
}

void RangeFilterEffect::setRange(float start, float end)
{
    program()->setUniformValue("rangeStart", start);
    program()->setUniformValue("rangeEnd", end);
}
