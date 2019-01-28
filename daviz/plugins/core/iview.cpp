#include "iview.h"
#include "icore.h"
#include "iradar.h"
#include <QDebug>

using namespace RadarDisplay;

IView::IView(QWidget *parent) :
    QWidget(parent),
    m_name(tr("Base view")),
    m_rangeMin(0),
    m_rangeMax(0),
    m_rangeStart(0),
    m_rangeEnd(0),
    m_layers(IView::PlotLayer | IView::TrackLayer)
{
}

QString IView::name() const
{
    return m_name;
}

void IView::setName(const QString &name)
{
    m_name = name;
}

qreal IView::rangeMinimum() const
{
    return m_rangeMin;
}

qreal IView::rangeMaximum() const
{
    return m_rangeMax;
}

QPair<qreal, qreal> IView::rangeBound() const
{
    return qMakePair(m_rangeMin, m_rangeMax);
}

void IView::setRangeBound(qreal start, qreal end)
{
    if (start > end || (start == m_rangeMin && end == m_rangeMax))
        return;
    m_rangeMin = start;
    m_rangeMax = end;
}

qreal IView::rangeStart() const
{
    return m_rangeStart;
}

qreal IView::rangeEnd() const
{
    return m_rangeEnd;
}

QPair<qreal, qreal> IView::range() const
{
    return qMakePair(m_rangeStart, m_rangeEnd);
}

IView::Selection IView::currentSelection() const
{
    return m_currentSelection;
}

void IView::setCurrentSelection(const IView::Selection &sel)
{
    if (m_currentSelection == sel)
        return;
    m_currentSelection = sel;
    updateSelection(sel);
    emit currentSelectionChanged(sel);
}

void IView::setRubberBand(const IView::Selection &sel)
{
    updateSelection(sel);
}

void IView::enableLayer(IView::Layer layer, bool enable)
{
    IView::Layers newLayers = m_layers;
    if (enable)
        newLayers |= layer;
    else
        newLayers ^= layer;
    if (newLayers != m_layers) {
        m_layers = newLayers;
        updateLayers(m_layers);
        emit layersChanged(m_layers);
    }
}

IView::Layers IView::layers() const
{
    return m_layers;
}

void IView::setRange(qreal start, qreal end)
{
    if (start > end || (start == m_rangeStart && end == m_rangeEnd))
        return;
    m_rangeStart = start;
    m_rangeEnd = end;
    updateRange(start, end);
    emit rangeChanged(start, end);
}

IView::Selection::Selection()
{
    setNone();
}

bool IView::Selection::operator ==(const IView::Selection &rhs) const
{
    return distanceStart == rhs.distanceStart
            && distanceEnd == rhs.distanceEnd
            && azimuthStart == rhs.azimuthStart
            && azimuthEnd == rhs.azimuthEnd
            && elevationStart == rhs.elevationStart
            && elevationEnd == rhs.elevationEnd;
}

bool IView::Selection::isNone() const
{
    return distanceStart == 0.
            && distanceEnd == 0.
            && azimuthStart == 0.
            && azimuthEnd == 0.
            && elevationStart == 0.
            && elevationEnd == 0.;
}

void IView::Selection::setNone()
{
    distanceStart = 0.;
    distanceEnd = 0.;
    azimuthStart = 0.;
    azimuthEnd = 0.;
    elevationStart = 0.;
    elevationEnd = 0.;
}

QString IView::Selection::toString() const
{
    if (isNone())
        return tr("None");
    else {
        QString result;
        QString distString;
        if (distanceStart > 0. || (ICore::currentRadar() && distanceEnd < ICore::currentRadar()->maxDistance())) {
            distString = QString("dist %1 to %2 km").arg(distanceStart, 0, 'f', 0).arg(distanceEnd, 0, 'f', 0);
            result += distString + " ";
        }
        QString azimString;
        if (azimuthStart != 0. || azimuthEnd != 360.) {
            azimString = QString("azim %1° to %2°").arg(azimuthStart, 0, 'f', 1).arg(azimuthEnd, 0, 'f', 1);
            result += azimString + " ";
        }
        QString elevString;
        if (elevationStart != 0. || elevationEnd != 90.) {
            elevString = QString("elev %1° to %2°").arg(elevationStart, 0, 'f', 1).arg(elevationEnd, 0, 'f', 1);
            result += elevString;
        }
        return result;
    }
}
