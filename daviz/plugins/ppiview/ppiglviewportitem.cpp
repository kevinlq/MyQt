#include "ppiglviewportitem.h"
#include "ppieffect.h"
#include <QColor>
#include <QDebug>
#include <QTimer>
#include <QMatrix4x4>
//#include <GL/glew.h>
#include <qglpainter.h>
#include <math.h>

using namespace RadarDisplay;

static const int SECTORS = 12;

PPIGLViewportItem::PPIGLViewportItem(QGraphicsItem *parent) :
    QGLGraphicsViewportItem(parent),
    m_distance(10000),
    m_radius(100),
    m_antennaPosition(0.0),
    m_ppiEffect(new PPIEffect)
{
    m_pointsGeometryInSector.resize(SECTORS);
}

PPIGLViewportItem::~PPIGLViewportItem()
{
    delete m_ppiEffect;
}

void PPIGLViewportItem::setRadius(qreal radius)
{
    if (radius > 0.0) {
        m_radius = radius;
        setRect(-radius, -radius, radius*2, radius*2);
        updateAntennaGeometry();
    }
}

void PPIGLViewportItem::setDistance(qreal distance)
{
    m_distance = distance;
}

void PPIGLViewportItem::setElevationRange(qreal start, qreal end)
{
    m_elevationStart = start;
    m_elevationEnd = end;
}

void PPIGLViewportItem::paintGL(QGLPainter *painter)
{
    QMatrix4x4 projMat;
    projMat.ortho(rect());
    painter->projectionMatrix() = projMat;
    painter->modelViewMatrix().setToIdentity();

    painter->clearAttributes();

    painter->setUserEffect(m_ppiEffect);
    m_ppiEffect->setAntennaPosition(m_antennaPosition);

    glEnable(GL_BLEND);
    m_ppiEffect->setColor(Qt::green);

    m_ppiEffect->setElevationRange(m_elevationStart, m_elevationEnd);

    glPointSize(2);
    for (int i = 0; i < SECTORS; i++) {
        painter->setVertexAttribute(QGL::Position, m_pointsGeometryInSector[i]);
        painter->draw(QGL::Points, m_pointsGeometryInSector[i].size());
    }
}

void PPIGLViewportItem::addPlot(const PlotData &plot)
{
    qreal r = plot.distance / m_distance * m_radius;
    qreal a = plot.azimuth / 180 * M_PI;
    QVector3DArray &pointArray = m_pointsGeometryInSector[getSector(plot.azimuth)];
    pointArray.append(r * sin(a), -r * cos(a), plot.elevation / 90.0);
}

void PPIGLViewportItem::clear()
{
    for (int i = 0; i < m_pointsGeometryInSector.size(); i++)
        m_pointsGeometryInSector[i].resize(0);
    m_antennaPosition = 0.0;
    update();
}

void PPIGLViewportItem::setAntennaPosition(qreal pos)
{
    qreal lastPosition = m_antennaPosition;
    m_antennaPosition = pos;

    int lastSector = getSector(lastPosition);
    int currentSector = getSector(pos);
    if (lastSector != currentSector) {
        m_pointsGeometryInSector[currentSector].resize(0);
    }
    update();
}

void PPIGLViewportItem::updateAntennaGeometry()
{
    m_antennaGeometry.resize(0);
    m_antennaGeometry.append(0.0, 0.0, 0.0);
    int subdivide = m_radius * 6;
    for (int i = 0; i < subdivide; i++) {
        qreal radian = (qreal)i / subdivide * 2 * M_PI;
        m_antennaGeometry.append(m_radius * cos(radian), m_radius * sin(radian), -1.0);
    }
    m_antennaGeometry.append(m_radius * cos(0.0), m_radius * sin(0.0), -1.0);
}

int PPIGLViewportItem::getSector(qreal degree)
{
    return (int)((degree + 360) / 360 * SECTORS) % SECTORS;
}
