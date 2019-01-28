#ifndef IVIEW_H
#define IVIEW_H

#include "core_global.h"
#include <QWidget>
#include <QString>
#include <QPair>
#include <QFlags>

namespace RadarDisplay {
class IRadar;

class CORE_EXPORT IView : public QWidget
{
    Q_OBJECT
public:
    class CORE_EXPORT Selection {
    public:
        enum Type {
            NoneSelection,
            ValueSelection
        };
        Selection();
        bool operator ==(const Selection &rhs) const;
        bool operator !=(const Selection &rhs) const { return !(*this == rhs); }
        bool isNone() const;
        void setNone();
        bool isValue() const { return !isNone(); }
        QString toString() const;

        qreal distanceStart;
        qreal distanceEnd;
        qreal azimuthStart;
        qreal azimuthEnd;
        qreal elevationStart;
        qreal elevationEnd;
    };

    enum Layer {
        PlotLayer = 1,
        TrackLayer = 2
    };
    Q_DECLARE_FLAGS(Layers, Layer)

    explicit IView(QWidget *parent = 0);
    QString name() const;
    void setName(const QString &name);
    virtual void active() {}
    virtual void deactive() {}

    qreal rangeMinimum() const;
    qreal rangeMaximum() const;
    QPair<qreal, qreal> rangeBound() const;
    void setRangeBound(qreal start, qreal end);

    qreal rangeStart() const;
    qreal rangeEnd() const;
    QPair<qreal, qreal> range() const;

    Selection currentSelection() const;
    void setCurrentSelection(const Selection &sel);
    void setRubberBand(const Selection &sel);

    void enableLayer(enum Layer layer, bool enable = true);
    IView::Layers layers() const;

signals:
    void rangeChanged(qreal /* start */, qreal /* end */);
    void currentSelectionChanged(const IView::Selection &sel);
    void layersChanged(const IView::Layers &layers);

public slots:
    virtual void setRadar(IRadar *radar) = 0;
    void setRange(qreal start, qreal end);

protected:
    virtual void updateRange(qreal /* start */, qreal /* end */) {}
    virtual void updateSelection(const Selection & /*sel*/) {}
    virtual void updateLayers(const Layers& /*layers*/) {}

private:
    QString m_name;
    qreal m_rangeMin, m_rangeMax;
    qreal m_rangeStart, m_rangeEnd;
    Selection m_currentSelection;
    Layers m_layers;
};
}
Q_DECLARE_OPERATORS_FOR_FLAGS(RadarDisplay::IView::Layers)
#endif // IVIEW_H
