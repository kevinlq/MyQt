#include "ppicontrol.h"
#include "ppiview.h"
#include "core/iradar.h"
#include "core/icore.h"
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
PPIControl::PPIControl(PPIView *ppi, QWidget *parent) :
    QWidget(parent),
    m_view(ppi),
    m_scale(1.0),
    m_reportMousePosition(false)
{
    QToolButton *btn = new QToolButton(this);
    btn->setIcon(QIcon(":/icons/zoom-original.png"));
    btn->setText(tr("Reset view"));
    btn->setToolTip(tr("Reset view"));
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(btn, SIGNAL(clicked()), SLOT(resetView()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(btn);
    layout->addStretch(0);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    ppi->installInputEventFilter(this);
    ppi->setCenter(QPointF(0.0, 0.0));

    setMinimumHeight(sizeHint().height());
    setMaximumHeight(sizeHint().height());

    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)), SLOT(updateTexts()));

    updateTexts();

    startTimer(1000);
}

PPIControl::~PPIControl()
{
    qDebug() << Q_FUNC_INFO;
    m_view->removeInputEventFilter(this);
}

void PPIControl::createActions()
{
}

bool PPIControl::eventFilter(QObject *object, QEvent *event)
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

bool PPIControl::wheelEventFilter(QWheelEvent *event)
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

bool PPIControl::mouseEventFilter(QMouseEvent *event)
{
    static bool dragging = false;
    static QPointF downPos;
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
            downPos = scenePos;
            break;
        case QEvent::MouseButtonRelease:
            QApplication::restoreOverrideCursor();
            if (!dragging)
                break;
            dragging = false;
            deltaPos = scenePos - downPos;
            m_origin = -deltaPos;
            m_view->setCenter(m_origin);
            updateTransformText();
            break;
        case QEvent::MouseMove:
            if (event->buttons() == Qt::RightButton)
                dragging = true;
            break;
        case QEvent::MouseButtonDblClick:
            QApplication::restoreOverrideCursor();
            dragging = false;
            m_origin = scenePos;
            m_view->setCenter(m_origin);
            updateTransformText();
            break;
        default:
            ;
        }
    } else if (event->buttons() == Qt::LeftButton || (event->buttons() == Qt::NoButton && event->button() == Qt::LeftButton)) {
        QPointF startRA;
        QPointF currentRA;
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
            startRA = m_view->getRA(selectDownPos.x(), selectDownPos.y());
            currentRA = m_view->getRA(scenePos.x(), scenePos.y());
            selection.distanceStart = qMin(startRA.x(), currentRA.x());
            selection.distanceEnd = qMax(startRA.x(), currentRA.x());
            selection.azimuthStart = qMin(startRA.y(), currentRA.y());
            selection.azimuthEnd = qMax(startRA.y(), currentRA.y());
            if (selection.azimuthEnd - selection.azimuthStart > 180)
                qSwap(selection.azimuthStart, selection.azimuthEnd);
            selection.elevationStart = 0.;
            selection.elevationEnd = 90.;
            m_view->setRubberBand(selection);
            break;
        default:
            ;
        }
    }
    event->accept();
    return true;
}

bool PPIControl::keyEventFilter(QKeyEvent *event)
{
    Q_UNUSED(event)
    return false;
}

bool PPIControl::enterEventFilter(QEvent *)
{
    m_reportMousePosition = true;
    return true;
}

bool PPIControl::leaveEventFilter(QEvent *)
{
    m_reportMousePosition = false;
    m_view->setCornerText(Qt::TopLeftCorner, QString());
    return true;
}

void PPIControl::timerEvent(QTimerEvent *)
{
    updateTimeText();
}

void PPIControl::resetView()
{
    m_view->setCenter(QPointF(0, 0));
    m_view->setScale(1.0);
    updateTransformText();
}

void PPIControl::updatePositionText()
{
    if (!m_reportMousePosition)
        return;
    if (!ICore::currentRadar())
        return;
    QPointF scenePos, radarPos;
    scenePos = m_view->scenePos(m_view->viewport()->mapFromGlobal(QCursor::pos()));
    radarPos.rx() = scenePos.x();
    radarPos.ry() = -scenePos.y();
    radarPos *= ICore::currentRadar()->maxDistance() / m_view->viewRadius();
    qreal dist, azim;
    carteToPolar(radarPos.x(), radarPos.y(), dist, azim);
    m_view->setCornerText(Qt::TopLeftCorner, tr("Distance:%1km\n Azimuth:%2°").arg(dist/1000, 6, 'f', 2).arg(azim, 6, 'f', 2));
}

void PPIControl::updateTimeText()
{
    m_view->setCornerText(Qt::BottomLeftCorner, QDateTime::currentDateTime().toString(tr("hh:mm:ss dddd\nyyyy-MM-dd")));
}

void PPIControl::updateTransformText()
{
    if (!ICore::currentRadar())
        return;
    QPointF center;
    center.rx() = m_view->center().x();
    center.ry() = -m_view->center().y();
    center *= ICore::currentRadar()->maxDistance() / m_view->viewRadius();
    qreal dist, azim;
    carteToPolar(center.x(), center.y(), dist, azim);
    m_view->setCornerText(Qt::TopRightCorner, tr(" Scale:%1x\nCenter:%2km %3°")
                         .arg(m_view->scale(), 6, 'f', 2)
                         .arg(dist/1000, 6, 'f', 2)
                         .arg(azim, 6, 'f', 2));
}

void PPIControl::updateTexts()
{
    updatePositionText();
    updateTimeText();
    updateTransformText();
}

void PPIControl::carteToPolar(qreal x, qreal y, qreal &r, qreal &a)
{
    r = sqrt(x*x + y*y);
    if (r < 1e-6)
        a = 0;
    else {
        a = asin(y/r) * 180 * M_1_PI;
        if (x > 0)
            a = 90 - a;
        else if (x < 0)
            a = 270 + a;
    }
}
