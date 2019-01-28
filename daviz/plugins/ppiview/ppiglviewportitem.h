#ifndef PPIGLVIEWPORTITEM_H
#define PPIGLVIEWPORTITEM_H

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

namespace RadarDisplay {
class PPIEffect;
class PPIGLViewportItem : public QGLGraphicsViewportItem
{
public:
    PPIGLViewportItem(QGraphicsItem *parent = 0);
    ~PPIGLViewportItem();
    void setRadius(qreal radius);
    void setDistance(qreal distance);
    void setElevationRange(qreal start, qreal end);
    void setAntennaPosition(qreal pos);
    void addPlot(const PlotData &plot);
    void clear();

protected:
    void paintGL(QGLPainter *painter);

private:
    void updateAntennaGeometry();
    int getSector(qreal degree);

    float m_elevationStart;
    float m_elevationEnd;
    qreal m_distance;
    qreal m_radius;
    qreal m_antennaPosition;
    QVector3DArray m_antennaGeometry;
    QVector<QVector3DArray> m_pointsGeometryInSector;
    PPIEffect *m_ppiEffect;
};
}

#endif // PPIGLVIEWPORTITEM_H
