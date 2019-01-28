#ifndef PPIVIEW_H
#define PPIVIEW_H

#include "core/icore.h"
#include "core/iview.h"

#include <QGraphicsView>
#include <QWidget>
#include <QPointF>
#include <QMap>

class QWheelEvent;
class QGraphicsScene;
class QGraphicsLineItem;
class QGraphicsSimpleTextItem;
namespace RadarDisplay {

enum ZValue_Layers {
    ZValue_CoordsLayer = -3,
    ZValue_SelectionLayer = -2,
    ZValue_GLLayer = -1,
    ZValue_DefaultLayer = 0,
    ZValue_ScanlineLayer = 1,
    ZValue_LabelLayer = 2
};

class IRadar;
class TrackItem;
class PPIGLViewportItem;
class CoordsItem;
class RangeBar;
class TextItem;
class SelectionItem;

class PPIView : public IView
{
    Q_OBJECT
public:
    explicit PPIView(QWidget *parent = 0);
    ~PPIView();
    float scale();
    void setScale(float _scale);
    QPointF center() const;
    void setCenter(const QPointF &center);
    QPointF scenePos(const QPoint &p) const;
    void installInputEventFilter(QObject *object);
    void removeInputEventFilter(QObject *object);
    void active();
    void deactive();
    void setCornerText(Qt::Corner corner, const QString &text);
    qreal viewRadius() const;
    QWidget *viewport() const;

signals:
    
public slots:
    void plotAdded(const PlotData &plot);
    void trackAdded(const TrackData &track);
    void trackRemoved(const TrackData &track);
    void trackTargetAdded(const TargetData &target);
    void antennaPositionChanged(float apos);
    void clearData();
    void setRadar(IRadar *_radar);

    QPointF getXY(float distance, float azimuth);
    QPointF getRA(float x, float y);

protected:
    void updateRange(qreal start, qreal end);
    void updateLayers(const Layers &layers);
    void updateSelection(const Selection &sel);

private:
    void createCornerLabels();
    void updateCornerTextPositions();

    IRadar *m_radar;
    RangeBar *m_rangeBar;
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
    QGraphicsLineItem *m_scanline;
    TextItem *m_topLeftLabel;
    TextItem *m_topRightLabel;
    TextItem *m_bottomLeftLabel;
    TextItem *m_bottomRightLabel;
    PPIGLViewportItem *m_glViewportItem;
    CoordsItem *m_coordsItem;
    SelectionItem *m_selectionItem;
    QMap<int, TrackItem *> m_trackMap;
    QMap<int, QPointF> m_trackLastPos;
    float m_scale;
    QPointF m_center;
};

}

#endif // PPIVIEW_H
