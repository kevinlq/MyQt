#include "ppiview.h"
#include "ppiglviewportitem.h"
#include "coordsitem.h"
#include "trackitem.h"
#include "core/iradar.h"
#include "core/icore.h"
#include "utils/rangebar.h"
#include "utils/textitem.h"
#include "utils/selectionitem.h"
#include <math.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QHBoxLayout>
#include <QDebug>
#include <QRectF>
#include <QPointF>
#include <QPen>
#include <QTransform>
#include <QWheelEvent>
#include <QEvent>
#include <QGraphicsSceneWheelEvent>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QGLWidget>
#include <QGLFormat>
#include <QAbstractScrollArea>
#include <QGraphicsSimpleTextItem>

using namespace RadarDisplay;

static const qreal VIEW_RADIUS = 500;

PPIView::PPIView(QWidget *parent) :
    IView(parent),
    m_radar(0),
    m_scale(1.0),
    m_center(0.0, 0.0)
{
    setName(tr("PPI View"));
    m_view = new QGraphicsView(this);

    m_scene = new QGraphicsScene;
    m_scene->setSceneRect(-VIEW_RADIUS, -VIEW_RADIUS, VIEW_RADIUS*2, VIEW_RADIUS*2);
    m_scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

    QGLFormat format;
    format.setSampleBuffers(true);
    format.setRgba(true);
    format.setOverlay(true);
    format.setAlpha(true);
    format.setSamples(2);
    QGLWidget *glWidget = new QGLWidget(format, this);
    m_view->setViewport(glWidget);
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    m_view->setScene(m_scene);
    m_view->setBackgroundBrush(Qt::black);
    m_view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    m_view->centerOn(0, 0);
    m_view->setContentsMargins(0, 0, 0, 0);
    m_view->setFrameShape(QFrame::NoFrame);
    m_view->setFixedSize(VIEW_RADIUS*2, VIEW_RADIUS*2);
    m_view->viewport()->setFixedSize(VIEW_RADIUS*2, VIEW_RADIUS*2);
    m_view->viewport()->setCursor(Qt::CrossCursor);
    m_view->viewport()->setMouseTracking(true);

    m_scanline = new QGraphicsLineItem(0,0,0,-VIEW_RADIUS);
    m_scanline->setZValue(ZValue_ScanlineLayer);
    m_scanline->setPen(QPen(Qt::white, 2));
    m_scanline->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    m_scene->addItem(m_scanline);

    createCornerLabels();

    m_coordsItem = new CoordsItem(Coords_FiveKilometers,
                                  Coords_OneKilometer);
    m_coordsItem->setRadius(VIEW_RADIUS);
    m_coordsItem->setZValue(ZValue_CoordsLayer);
    m_scene->addItem(m_coordsItem);

    m_selectionItem = new SelectionItem;
    m_selectionItem->setZValue(ZValue_SelectionLayer);
    m_scene->addItem(m_selectionItem);

    m_glViewportItem = new PPIGLViewportItem;
    m_glViewportItem->setRadius(VIEW_RADIUS);
    m_glViewportItem->setZValue(ZValue_GLLayer);
    m_scene->addItem(m_glViewportItem);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(m_view);
    m_rangeBar = new RangeBar(Qt::Vertical, 0., 90., this);
    m_rangeBar->setReversed(true);
    m_rangeBar->setTicks(9, 10);
    layout->addWidget(m_rangeBar);
    connect(m_rangeBar, SIGNAL(rangeChanged(qreal,qreal)), SLOT(setRange(qreal,qreal)));

    setRangeBound(0., 90.);
    setRange(0., 90.);
//    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

PPIView::~PPIView()
{
    qDebug() << Q_FUNC_INFO;
}

float PPIView::scale()
{
    return m_scale;
}

void PPIView::setScale(float _scale)
{
    m_view->scale(_scale/m_scale, _scale/m_scale);
    m_scale = _scale;
    m_center = scenePos(QPoint(VIEW_RADIUS, VIEW_RADIUS));
    updateCornerTextPositions();
}

QPointF PPIView::center() const
{
    return m_center;
}

void PPIView::setCenter(const QPointF &center)
{
    m_view->centerOn(center.x(), center.y());
    m_center = scenePos(QPoint(VIEW_RADIUS, VIEW_RADIUS));
    updateCornerTextPositions();
}

QPointF PPIView::scenePos(const QPoint &p) const
{
    return m_view->mapToScene(p);
}

void PPIView::installInputEventFilter(QObject *object)
{
    m_view->viewport()->installEventFilter(object);
}

void PPIView::removeInputEventFilter(QObject *object)
{
    m_view->viewport()->removeEventFilter(object);
}

void PPIView::active()
{
//    setRadar(ICore::currentRadar());
}

void PPIView::deactive()
{
//    setRadar(0);
}

void PPIView::setCornerText(Qt::Corner corner, const QString &text)
{
    TextItem *ti = 0;

    if (corner == Qt::TopLeftCorner)
        ti = m_topLeftLabel;
    else if (corner == Qt::TopRightCorner)
        ti = m_topRightLabel;
    else if (corner == Qt::BottomLeftCorner)
        ti = m_bottomLeftLabel;
    else if (corner == Qt::BottomRightCorner)
        ti = m_bottomRightLabel;
    if (ti)
        ti->setText(text);

    updateCornerTextPositions();
}

qreal PPIView::viewRadius() const
{
    return VIEW_RADIUS;
}

QWidget *PPIView::viewport() const
{
    return m_view->viewport();
}

void PPIView::setRadar(IRadar *_radar)
{
    if (_radar == m_radar)
        return;
    if (m_radar) {
        m_radar->disconnect(this);
        qDeleteAll(m_trackMap.values());
        m_trackMap.clear();
        m_trackLastPos.clear();
    }
    m_radar = _radar;
    if (!m_radar)
        return;
    connect(m_radar, SIGNAL(antennaPositionChanged(float)), SLOT(antennaPositionChanged(float)));
    connect(m_radar, SIGNAL(plotAdded(PlotData)), SLOT(plotAdded(PlotData)));
    connect(m_radar, SIGNAL(trackAdded(TrackData)), SLOT(trackAdded(TrackData)));
    connect(m_radar, SIGNAL(trackRemoved(TrackData)), SLOT(trackRemoved(TrackData)));
    connect(m_radar, SIGNAL(trackTargetAdded(TargetData)), SLOT(trackTargetAdded(TargetData)));
    connect(m_radar, SIGNAL(dataCleared()), SLOT(clearData()));

    m_glViewportItem->setDistance(m_radar->maxDistance());
    m_glViewportItem->clear();
    m_coordsItem->setDistance(m_radar->maxDistance());
    antennaPositionChanged(0.0);
}

void PPIView::updateRange(qreal start, qreal end)
{
    m_glViewportItem->setElevationRange(start, end);
    QString text = tr("Elevation: %1°to %2°").arg(start, 0, 'f', 1).arg(end, 0, 'f', 1);
    setCornerText(Qt::BottomRightCorner, text);
}

void PPIView::updateLayers(const IView::Layers &layers)
{
    if (layers & IView::PlotLayer)
        m_glViewportItem->show();
    else
        m_glViewportItem->hide();

    if (layers & IView::TrackLayer) {
        foreach (TrackItem *item, m_trackMap.values())
            item->show();
    } else {
        foreach (TrackItem *item, m_trackMap.values())
            item->hide();
    }
}

void PPIView::updateSelection(const IView::Selection &sel)
{
    if (sel.isNone()) {
        m_selectionItem->hide();
        m_selectionItem->setPath(QPainterPath());
    } else {
        QPointF p1 = getXY(sel.distanceStart, sel.azimuthStart);
        QPointF p2 = getXY(sel.distanceEnd, sel.azimuthStart);
        QPointF p3 = getXY(sel.distanceStart, sel.azimuthEnd);
        QPointF p4 = getXY(sel.distanceEnd, sel.azimuthEnd);
        qreal r1 = sel.distanceStart / m_radar->maxDistance() * VIEW_RADIUS;
        qreal r2 = sel.distanceEnd / m_radar->maxDistance() * VIEW_RADIUS;
        qreal degrees;
        if (sel.azimuthStart <= sel.azimuthEnd)
            degrees = sel.azimuthEnd - sel.azimuthStart;
        else
            degrees = 360.0 + sel.azimuthEnd - sel.azimuthStart;
        QPainterPath path;
        path.moveTo(p1);
        path.lineTo(p2);
        path.arcTo(-r2, -r2, r2*2, r2*2, 90 - sel.azimuthStart, -degrees);
        path.lineTo(p3);
        path.arcTo(-r1, -r1, r1*2, r1*2, 90 - sel.azimuthEnd, degrees);
        m_selectionItem->setPath(path);
        m_selectionItem->show();
    }
}

void PPIView::plotAdded(const PlotData &plot)
{
    m_glViewportItem->addPlot(plot);
}

void PPIView::trackAdded(const TrackData &track)
{
    if (m_trackMap.contains(track.id))
        trackRemoved(track);
    TrackItem *item = new TrackItem(track);
    item->setZValue(ZValue_DefaultLayer);
    if (!(layers() & IView::TrackLayer))
        item->hide();
    m_scene->addItem(item);
    m_trackMap.insert(track.id, item);
    m_trackLastPos.insert(track.id, QPointF());
}

void PPIView::trackRemoved(const TrackData &track)
{
    TrackItem *item = m_trackMap.value(track.id);
    if (!item)
        return;
    delete item;
    m_trackMap.remove(track.id);
    m_trackLastPos.remove(track.id);
}

void PPIView::trackTargetAdded(const TargetData &target)
{
    TrackData trackData(target.trackId);
    if (!m_trackMap.contains(target.trackId)) {
        trackAdded(trackData);
    }

    TrackItem *trackItem = m_trackMap.value(target.trackId);
    trackItem->addPoint(getXY(target.distance, target.azimuth));
}

void PPIView::antennaPositionChanged(float apos)
{
    m_scanline->setRotation(apos);
    m_glViewportItem->setAntennaPosition(apos);
}

void PPIView::clearData()
{
    m_glViewportItem->clear();
    antennaPositionChanged(0.0);
    foreach (TrackItem *item, m_trackMap.values()) {
        delete item;
    }
    m_trackMap.clear();
    m_trackLastPos.clear();
}

QPointF PPIView::getXY(float distance, float azimuth)
{
    float r, a, x, y;
    r = distance/m_radar->maxDistance()*VIEW_RADIUS;
    a = azimuth*M_PI/180.0;
    x = r*sinf(a);
    y = -r*cosf(a);
    return QPointF(x, y);
}

QPointF PPIView::getRA(float x, float y)
{
    float r, a;
    r = sqrt(x * x + y * y);
    a = asinf(x / r) * 180.0 * M_1_PI;
    if (y > 0)
        a = 180. - a;
    else if (x < 0)
        a += 360.;
    r = r / VIEW_RADIUS * m_radar->maxDistance();
    return QPointF(r, a);
}

void PPIView::createCornerLabels()
{
    m_topLeftLabel = new TextItem;
    m_topLeftLabel->setZValue(ZValue_LabelLayer);
    m_topLeftLabel->setBackgroundColor(Qt::black);
    m_topLeftLabel->setBrush(Qt::white);
    m_topLeftLabel->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    m_topLeftLabel->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    m_scene->addItem(m_topLeftLabel);
    m_topLeftLabel->setPos(100,100);


    m_topRightLabel = new TextItem;
    m_topRightLabel->setZValue(ZValue_LabelLayer);
    m_topRightLabel->setBackgroundColor(Qt::black);
    m_topRightLabel->setBrush(Qt::white);
    m_topRightLabel->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    m_topRightLabel->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    m_scene->addItem(m_topRightLabel);

    m_bottomLeftLabel = new TextItem;
    m_bottomLeftLabel->setZValue(ZValue_LabelLayer);
    m_bottomLeftLabel->setBackgroundColor(Qt::black);
    m_bottomLeftLabel->setBrush(Qt::white);
    m_bottomLeftLabel->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    m_bottomLeftLabel->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    m_scene->addItem(m_bottomLeftLabel);

    m_bottomRightLabel = new TextItem;
    m_bottomRightLabel->setZValue(ZValue_LabelLayer);
    m_bottomRightLabel->setBackgroundColor(Qt::black);
    m_bottomRightLabel->setBrush(Qt::white);
    m_bottomRightLabel->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    m_bottomRightLabel->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    m_scene->addItem(m_bottomRightLabel);
}

void PPIView::updateCornerTextPositions()
{
    QFontMetricsF fm(font());
    QRectF viewRect(-VIEW_RADIUS, -VIEW_RADIUS, 2 * VIEW_RADIUS, 2 * VIEW_RADIUS);
    QRectF textRect;
    QPointF pos;

    textRect = fm.boundingRect(viewRect, Qt::AlignTop | Qt::AlignLeft, m_topLeftLabel->text());
    pos = textRect.topLeft() / m_scale + m_center;
    m_topLeftLabel->setPos(pos);

    textRect = fm.boundingRect(viewRect, Qt::AlignTop | Qt::AlignRight, m_topRightLabel->text());
    pos = textRect.topLeft() / m_scale + m_center;
    m_topRightLabel->setPos(pos);

    textRect = fm.boundingRect(viewRect, Qt::AlignBottom | Qt::AlignLeft, m_bottomLeftLabel->text());
    pos = textRect.topLeft() / m_scale + m_center;
    m_bottomLeftLabel->setPos(pos);

    textRect = fm.boundingRect(viewRect, Qt::AlignBottom | Qt::AlignRight, m_bottomRightLabel->text());
    pos = textRect.topLeft() / m_scale + m_center;
    m_bottomRightLabel->setPos(pos);
}
