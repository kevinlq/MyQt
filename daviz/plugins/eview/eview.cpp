#include "eview.h"
#include "eviewportitem.h"
#include "coordsitem.h"
#include "trackitem.h"
#include "trackpathitem.h"
#include "core/iradar.h"
#include "core/iview.h"
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
#include <QPainterPath>
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

namespace {
static const float VIEW_RADIUS = 500;
static const int MARGIN = 4;
static const qreal DEFAULT_RANGE_MIN = 0.;
static const qreal DEFAULT_RANGE_MAX = 10.;
static const int DEFAULT_TICKS = 10;
}

EView::EView(QWidget *parent) :
    IView(parent),
    m_radar(0),
    m_scale(1.0),
    m_center(0.0, 0.0)
{
    setName(tr("E View"));
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
    glWidget->makeCurrent();
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

    m_scanline = new QGraphicsLineItem(0, -VIEW_RADIUS, 0, VIEW_RADIUS);
    m_scanline->setZValue(ZValue_ScanlineLayer);
    m_scanline->setPen(QPen(Qt::white, 2));
    m_scanline->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    m_scene->addItem(m_scanline);

    createCornerLabels();

    m_coordsItem = new CoordsItem(Coords_TenDegrees,
                                  Coords_OneDegree);
    m_coordsItem->setRadius(VIEW_RADIUS - MARGIN);
    m_coordsItem->setZValue(ZValue_CoordsLayer);
    m_scene->addItem(m_coordsItem);

    m_selectionItem = new SelectionItem;
    m_selectionItem->setZValue(ZValue_SelectionLayer);
    m_scene->addItem(m_selectionItem);

    m_glViewportItem = new EViewportItem;
    m_glViewportItem->setRadius(VIEW_RADIUS - MARGIN);
    m_glViewportItem->setZValue(ZValue_GLLayer);
    m_scene->addItem(m_glViewportItem);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(m_view);
    m_rangeBar = new RangeBar(Qt::Vertical, DEFAULT_RANGE_MIN, DEFAULT_RANGE_MAX, this);
    m_rangeBar->setReversed(true);
    m_rangeBar->setTicks(DEFAULT_TICKS, DEFAULT_TICKS);
    layout->addWidget(m_rangeBar);
    connect(m_rangeBar, SIGNAL(rangeChanged(qreal,qreal)), SLOT(setRange(qreal,qreal)));

    setRangeBound(DEFAULT_RANGE_MIN, DEFAULT_RANGE_MAX);
    setRange(DEFAULT_RANGE_MIN, DEFAULT_RANGE_MAX);
//    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

EView::~EView()
{
    qDebug() << Q_FUNC_INFO;
}

float EView::scale()
{
    return m_scale;
}

void EView::setScale(float _scale)
{
    m_view->scale(_scale/m_scale, _scale/m_scale);
    m_scale = _scale;
    m_center = scenePos(QPoint(VIEW_RADIUS, VIEW_RADIUS));
    updateCornerTextPositions();
}

QPointF EView::center() const
{
    return m_center;
}

void EView::setCenter(const QPointF &center)
{
    m_view->centerOn(center.x(), center.y());
    m_center = scenePos(QPoint(VIEW_RADIUS, VIEW_RADIUS));
    updateCornerTextPositions();
}

QPointF EView::scenePos(const QPoint &p) const
{
    return m_view->mapToScene(p);
}

void EView::installInputEventFilter(QObject *object)
{
    m_view->viewport()->installEventFilter(object);
}

void EView::removeInputEventFilter(QObject *object)
{
    m_view->viewport()->removeEventFilter(object);
}

void EView::active()
{
//    setRadar(ICore::currentRadar());
}

void EView::deactive()
{
//    setRadar(0);
}

void EView::setCornerText(Qt::Corner corner, const QString &text)
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

qreal EView::viewRadius() const
{
    return VIEW_RADIUS - MARGIN;
}

QWidget *EView::viewport() const
{
    return m_view->viewport();
}

void EView::setRadar(IRadar *_radar)
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

    m_glViewportItem->setMaxDistance(m_radar->maxDistance());
    m_glViewportItem->clear();
    m_rangeBar->blockSignals(true);
    m_rangeBar->setRangeBound(0., m_radar->maxDistance() / 1000.0);
    m_rangeBar->setRange(0., m_radar->maxDistance() / 1000.0);
    m_rangeBar->blockSignals(false);
    setRangeBound(0., m_radar->maxDistance() / 1000.0);
    setRange(0., m_radar->maxDistance() / 1000.0);
    antennaPositionChanged(0.0);
}

void EView::updateRange(qreal start, qreal end)
{
    m_glViewportItem->setDistanceRange(start * 1000.0, end * 1000.0);
    QString text = tr("Distance: %1km to %2km").arg(start, 0, 'f', 1).arg(end, 0, 'f', 1);
    setCornerText(Qt::BottomRightCorner, text);
}

void EView::updateLayers(const IView::Layers &layers)
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

void EView::updateSelection(const IView::Selection &sel)
{
    if (sel.isNone()) {
        m_selectionItem->hide();
        m_selectionItem->setPath(QPainterPath());
    } else {
        QPointF topLeft = getXY(sel.azimuthStart, sel.elevationEnd);
        QPointF bottomRight = getXY(sel.azimuthEnd, sel.elevationStart);
        QPainterPath path;
        path.addRect(QRectF(topLeft, bottomRight));
        m_selectionItem->setPath(path);
        m_selectionItem->show();
    }
}

void EView::plotAdded(const PlotData &plot)
{
    m_glViewportItem->addPlot(plot);
}

void EView::trackAdded(const TrackData &track)
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

void EView::trackRemoved(const TrackData &track)
{
    TrackItem *item = m_trackMap.value(track.id);
    if (!item)
        return;
    delete item;
    m_trackMap.remove(track.id);
    m_trackLastPos.remove(track.id);
}

void EView::trackTargetAdded(const TargetData &target)
{
    TrackData trackData(target.trackId);
    if (!m_trackMap.contains(target.trackId)) {
        trackAdded(trackData);
    }

    TrackItem *trackItem = m_trackMap.value(target.trackId);
    trackItem->addPoint(getXY(target.azimuth, target.elevation));
}

void EView::antennaPositionChanged(float apos)
{
    QPointF p = getXY(apos, 0.);
    m_scanline->setPos(p.x(), 0);
    m_glViewportItem->setAntennaPosition(apos);
}

void EView::clearData()
{
    m_glViewportItem->clear();
    antennaPositionChanged(0.0);
    foreach (TrackItem *item, m_trackMap.values()) {
        delete item;
    }
    m_trackMap.clear();
    m_trackLastPos.clear();
}

QPointF EView::getXY(float azimuth, float elevation) const
{
    float x, y;
    x = (VIEW_RADIUS - MARGIN) * 2 * (-0.5 + qBound(0.f, azimuth, 360.f) / 360.0);
    y = (VIEW_RADIUS - MARGIN) * 2 * (0.5 - qBound(0.f, elevation, 90.f) / 90.0);
    return QPointF(x, y);
}

QPointF EView::getAE(float x, float y) const
{
    float azim, elev;
    azim = (qBound(-VIEW_RADIUS + MARGIN, x, VIEW_RADIUS - MARGIN) / (VIEW_RADIUS - MARGIN) / 2 + 0.5) * 360.0;
    elev = -(qBound(-VIEW_RADIUS + MARGIN, y, VIEW_RADIUS - MARGIN) / (VIEW_RADIUS - MARGIN) / 2 - 0.5) * 90.0;
    return QPointF(azim, elev);
}

void EView::createCornerLabels()
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

void EView::updateCornerTextPositions()
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
