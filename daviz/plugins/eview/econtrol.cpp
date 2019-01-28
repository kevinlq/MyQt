#include "econtrol.h"
#include "eview.h"
#include "core/iradar.h"
#include "core/icore.h"
#include "core/panelwidget.h"
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTime>
#include <QHBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QActionGroup>
#include <QLabel>
#include <QSpacerItem>
#include <QApplication>
#include <QAction>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QTimer>
#include <QDateTime>
#include <math.h>

using namespace RadarDisplay;
EControl::EControl(EView *view, QObject *parent) :
    QObject(parent),
    m_view(view),
    m_scale(1.0),
    m_reportMousePosition(false)
{
    view->installInputEventFilter(this);
    view->setCenter(QPointF(0.0, 0.0));

    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)), SLOT(updateTexts()));
    //    connect(ICore::instance(), SIGNAL(currentViewChanged(IView*)), SLOT(currentViewChanged(IView*)));

    updateTexts();

    startTimer(1000);
}

EControl::~EControl()
{
    m_view->removeInputEventFilter(this);
}

void EControl::createActions()
{
}

bool EControl::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object)
    switch (event->type()) {
    case QEvent::Wheel:
        return wheelEventFilter(static_cast<QWheelEvent *>(event));
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::MouseButtonDblClick:
        return mouseEventFilter(static_cast<QMouseEvent *>(event));
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
        return keyEventFilter(static_cast<QKeyEvent *>(event));
    case QEvent::Enter:
        return enterEventFilter(event);
    case QEvent::Leave:
        return leaveEventFilter(event);
    case QEvent::HoverMove:
    default:
        return false;
    }
}

bool EControl::wheelEventFilter(QWheelEvent *event)
{
    const float scaleFactor = 1.2;
    event = static_cast<QWheelEvent *>(event);
    if (event->delta() > 0) {
        if (m_scale < 1.5) {
            m_scale *= scaleFactor;
            m_view->setScale(m_scale);
        }
    } else {
        if (m_scale > 0.5) {
            m_scale /= scaleFactor;
            m_view->setScale(m_scale);
        }
    }
    event->accept();
    updateTransformText();
    return true;
}

bool EControl::mouseEventFilter(QMouseEvent *event)
{
    static bool isDragging = false;
    static QPointF dragDownPos;
    QPointF scenePos, deltaPos;

    static bool isSelecting = false;
    static QPointF selectDownPos;
    static IView::Selection selection;

    updatePositionText();

    scenePos = m_view->scenePos(event->pos());
    if (event->buttons() == Qt::RightButton || (event->buttons() == Qt::NoButton && event->button() == Qt::RightButton)) {
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            QApplication::setOverrideCursor(Qt::OpenHandCursor);
            dragDownPos = scenePos;
            break;
        case QEvent::MouseButtonRelease:
            QApplication::restoreOverrideCursor();
            if (!isDragging)
                break;
            isDragging = false;
            deltaPos = scenePos - dragDownPos;
            m_origin = -deltaPos;
            m_view->setCenter(m_origin);
            updateTransformText();
            break;
        case QEvent::MouseMove:
            if (event->buttons() == Qt::RightButton)
                isDragging = true;
            break;
        case QEvent::MouseButtonDblClick:
            QApplication::restoreOverrideCursor();
            isDragging = false;
            m_origin = scenePos;
            m_view->setCenter(m_origin);
            updateTransformText();
            break;
        default:
            ;
        }
    } else if (event->buttons() == Qt::LeftButton || (event->buttons() == Qt::NoButton && event->button() == Qt::LeftButton)) {
        QPointF topLeftAE;
        QPointF bottomRightAE;
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            selectDownPos = scenePos;
            break;
        case QEvent::MouseButtonRelease:
            if (!isSelecting)
                break;
            isSelecting = false;
            m_view->setCurrentSelection(selection);
            break;
        case QEvent::MouseMove:
            isSelecting = true;
            topLeftAE = m_view->getAE(qMin(selectDownPos.x(), scenePos.x()), qMin(selectDownPos.y(), scenePos.y()));
            bottomRightAE = m_view->getAE(qMax(selectDownPos.x(), scenePos.x()), qMax(selectDownPos.y(), scenePos.y()));
            selection.distanceStart = 0.;
            if (ICore::currentRadar())
                selection.distanceEnd = ICore::currentRadar()->maxDistance();
            selection.azimuthStart = topLeftAE.x();
            selection.azimuthEnd = bottomRightAE.x();
            selection.elevationStart = bottomRightAE.y();
            selection.elevationEnd = topLeftAE.y();
            m_view->setRubberBand(selection);
            break;
        default:
            ;
        }
    }
    event->accept();
    return true;
}

bool EControl::keyEventFilter(QKeyEvent *event)
{
    Q_UNUSED(event)
    return false;
}

bool EControl::enterEventFilter(QEvent *)
{
    m_reportMousePosition = true;
    return true;
}

bool EControl::leaveEventFilter(QEvent *)
{
    m_reportMousePosition = false;
    m_view->setCornerText(Qt::TopLeftCorner, QString());
    return true;
}

void EControl::timerEvent(QTimerEvent *)
{
    updateTimeText();
}

/*
void EControl::currentViewChanged(IView *view)
{
    if (!inPanel())
        return;
    if (view == m_view)
        setPanelVisible(true);
    else
        setPanelVisible(false);
}
*/

void EControl::resetView()
{
    m_view->setCenter(QPointF(0, 0));
    m_view->setScale(1.0);
    updateTransformText();
}

void EControl::updatePositionText()
{
    if (!m_reportMousePosition)
        return;
    if (!ICore::currentRadar())
        return;
    QPointF scenePos;
    scenePos = m_view->scenePos(m_view->viewport()->mapFromGlobal(QCursor::pos()));
    qreal azim, elev;
    azim = scenePos.x() * 180.0 / m_view->viewRadius() + 180.0;
    elev = -scenePos.y() * 45.0 / m_view->viewRadius() + 45.0;
    m_view->setCornerText(Qt::TopLeftCorner, tr("Azimuth:%1°\n Elevation:%2°").arg(azim, 0, 'f', 2).arg(elev, 0, 'f', 2));
}

void EControl::updateTimeText()
{
    m_view->setCornerText(Qt::BottomLeftCorner, QDateTime::currentDateTime().toString(tr("hh:mm:ss dddd\nyyyy-MM-dd")));
}

void EControl::updateTransformText()
{
    if (!ICore::currentRadar())
        return;
    QPointF center = m_view->center();
    qreal azim, elev;
    azim = center.x() * 180.0 / m_view->viewRadius();
    elev = -center.y() * 45.0 / m_view->viewRadius();
    m_view->setCornerText(Qt::TopRightCorner, tr(" Scale:%1x\nOrigin:(Azim:%2°, Elev:%3°)")
                          .arg(m_view->scale(), 0, 'f', 2)
                          .arg(azim, 0, 'f', 2)
                          .arg(elev, 0, 'f', 2));
}

void EControl::updateTexts()
{
    updatePositionText();
    updateTimeText();
    updateTransformText();
}

/*
bool EControl::inPanel() const
{
    if (!parentWidget())
        return false;
    PanelWidget *panel = qobject_cast<PanelWidget *>(parentWidget());
    return (panel != 0);
}

void EControl::setPanelVisible(bool enable)
{
    PanelWidget *panel = qobject_cast<PanelWidget *>(parentWidget());
    if (!panel)
        return;
    panel->setVisible(enable);
}
*/
