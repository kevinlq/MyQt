#ifndef EVIEWPORTITEM_H
#define EVIEWPORTITEM_H

#include "core/icore.h"
#include <QVector2D>
//#include <GL/glew.h>
#if QT_VERSION >= 0x050000
#include "utils/qglgraphicsviewportitem.h"
#else
#include <qglgraphicsviewportitem.h>
#endif
#include <qgeometrydata.h>
#include <qvector3darray.h>
#include <QGLFramebufferObjectSurface>

class QOpenGLFramebufferObject;
namespace RadarDisplay {
class RangeFilterEffect;
class SweepEffect;
class EViewportItem : public QGLGraphicsViewportItem
{
public:
    EViewportItem(QGraphicsItem *parent = 0);
    ~EViewportItem();
    void setRadius(qreal radius);
    void setMaxDistance(qreal distance);
    void setDistanceRange(qreal start, qreal end);
    void setAntennaPosition(qreal pos);
    void addPlot(const PlotData &plot);
    void clear();

protected:
    void paintGL(QGLPainter *painter);

private:
    void updateAntennaGeometry();
    int getSector(qreal degree);

    float m_distanceStart;
    float m_distanceEnd;
    qreal m_distanceMax;
    qreal m_radius;
    qreal m_antennaPosition;
    QVector3DArray m_antennaGeometry;
    QVector<QVector3DArray> m_pointsGeometryInSector;
    RangeFilterEffect *m_rangeFilterEffect;
    SweepEffect *m_sweepEffect;
    QOpenGLFramebufferObject *m_fbo;
    QGLFramebufferObjectSurface m_fboSurface;
};
}

#endif // EVIEWPORTITEM_H
