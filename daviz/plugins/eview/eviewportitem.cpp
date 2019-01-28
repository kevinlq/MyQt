#include "eviewportitem.h"
#include "rangefiltereffect.h"
#include "sweepeffect.h"
#include <QColor>
#include <QDebug>
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLFramebufferObject>
//#include <GL/glew.h>
#include <qglpainter.h>
#include <math.h>

using namespace RadarDisplay;

static const int SECTORS = 12;

EViewportItem::EViewportItem(QGraphicsItem *parent) :
    QGLGraphicsViewportItem(parent),
    m_distanceMax(10000),
    m_radius(100),
    m_antennaPosition(0.0),
    m_rangeFilterEffect(new RangeFilterEffect),
    m_sweepEffect(new SweepEffect),
    m_fbo(0)
{
    m_pointsGeometryInSector.resize(SECTORS);
}

EViewportItem::~EViewportItem()
{
    delete m_sweepEffect;
    if (m_fbo)
        delete m_fbo;
}

void EViewportItem::setRadius(qreal radius)
{
    if (radius > 0.0) {
        m_radius = radius;
        setRect(-radius, -radius, radius*2, radius*2);
        if (m_fbo)
            delete m_fbo;
        QOpenGLFramebufferObjectFormat fmt;
        fmt.setSamples(4);
        fmt.setAttachment(QOpenGLFramebufferObject::Depth);
        m_fbo = new QOpenGLFramebufferObject(radius * 2, radius * 2);
        m_fboSurface.setFramebufferObject(m_fbo);
        //        updateAntennaGeometry();
    }
}

void EViewportItem::setMaxDistance(qreal distance)
{
    m_distanceMax = distance;
}

void EViewportItem::setDistanceRange(qreal start, qreal end)
{
    m_distanceStart = start;
    m_distanceEnd = end;
}

void EViewportItem::paintGL(QGLPainter *painter)
{
    Q_ASSERT(m_fbo);

    {
        painter->modelViewMatrix().push();
        painter->projectionMatrix().push();
        painter->pushSurface(&m_fboSurface);

        QMatrix4x4 projMat;
        projMat.ortho(rect());
        painter->projectionMatrix() = projMat;
        painter->modelViewMatrix().setToIdentity();

        glClearColor(0., 0., 0., 0.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        painter->setUserEffect(m_rangeFilterEffect);
        m_rangeFilterEffect->setColor(Qt::green);
        m_rangeFilterEffect->setRange(m_distanceStart / m_distanceMax, m_distanceEnd / m_distanceMax);

        glPointSize(2);
        glDisable(GL_BLEND);
        for (int i = 0; i < SECTORS; i++) {
            painter->setVertexAttribute(QGL::Position, m_pointsGeometryInSector[i]);
            painter->draw(QGL::Points, m_pointsGeometryInSector[i].size());
        }

        painter->setUserEffect(0);

        painter->popSurface();
        painter->projectionMatrix().pop();
        painter->modelViewMatrix().pop();
    }

    {
        QMatrix4x4 projMat;
        projMat.ortho(rect());
        painter->projectionMatrix() = projMat;
        painter->modelViewMatrix().setToIdentity();

//        glClearColor(0., 0., 0., 0.);
//        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, m_fbo->texture());
        QVector3DArray rectGeometry;
        rectGeometry << QVector3D(-m_radius, m_radius, 0)
                     << QVector3D(m_radius, m_radius, 0)
                     << QVector3D(m_radius, -m_radius, 0)
                     << QVector3D(-m_radius, -m_radius, 0);
        painter->setVertexAttribute(QGL::Position, rectGeometry);
        QVector3DArray rectTexCoord;
        rectTexCoord << QVector2D(0, 1)
                     << QVector2D(1, 1)
                     << QVector2D(1, 0)
                     << QVector2D(0, 0);
        painter->setVertexAttribute(QGL::TextureCoord0, rectTexCoord);

        painter->setUserEffect(m_sweepEffect);
        m_sweepEffect->setAntennaPosition(m_antennaPosition);

//        painter->setStandardEffect(QGL::FlatReplaceTexture2D);

        glEnable(GL_BLEND);
        painter->draw(QGL::TriangleFan, 4);

        painter->setUserEffect(0);

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void EViewportItem::addPlot(const PlotData &plot)
{
    qreal x, y;
    x = m_radius * 2 * (-0.5 + plot.azimuth / 360.0);
    y = m_radius * 2 * (-0.5 + plot.elevation / 90.0);
    QVector3DArray &pointArray = m_pointsGeometryInSector[getSector(plot.azimuth)];
    pointArray.append(x, y, plot.distance / m_distanceMax);
    //    pointArray.append(x, y, 1.);
}

void EViewportItem::clear()
{
    for (int i = 0; i < m_pointsGeometryInSector.size(); i++)
        m_pointsGeometryInSector[i].resize(0);
    m_antennaPosition = 0.0;
    update();
}

void EViewportItem::setAntennaPosition(qreal pos)
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

void EViewportItem::updateAntennaGeometry()
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

int EViewportItem::getSector(qreal degree)
{
    return (int)((degree + 360) / 360 * SECTORS) % SECTORS;
}
