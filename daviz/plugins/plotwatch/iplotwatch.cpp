#include "iplotwatch.h"
using namespace RadarDisplay;

IPlotWatch::IPlotWatch(QObject *parent) :
    QObject(parent),
    m_widget(0),
    m_abilities(IPlotWatch::NoAbility),
    m_state(IPlotWatch::Running)
{
}

IPlotWatch::~IPlotWatch()
{
}

IPlotWatch::Abilities IPlotWatch::abilities() const
{
    return m_abilities;
}

void IPlotWatch::setAbilities(IPlotWatch::Abilities abilities)
{
    m_abilities = abilities;
}

IPlotWatch::State IPlotWatch::state() const
{
    return m_state;
}

void IPlotWatch::setState(IPlotWatch::State _state)
{
    if (m_state != _state)
        m_state = _state;
}

QIcon IPlotWatch::icon() const
{
    return m_icon;
}

void IPlotWatch::setIcon(const QIcon &_icon)
{
    m_icon = _icon;
}

QString IPlotWatch::text() const
{
    return m_text;
}

void IPlotWatch::setText(const QString &_text)
{
    m_text = _text;
}

QWidget *IPlotWatch::widget() const
{
    return m_widget;
}

void IPlotWatch::setWidget(QWidget *widget)
{
    m_widget = widget;
}

void IPlotWatch::plotRemoveAll()
{
}

void IPlotWatch::plotAdded(const PlotData &plot)
{
    Q_UNUSED(plot)
}

void IPlotWatch::antennaPositionChanged(float degree)
{
    Q_UNUSED(degree)
}

void IPlotWatch::pause()
{
}

void IPlotWatch::resume()
{
}

void IPlotWatch::config()
{
}

void IPlotWatch::clear()
{
}

void IPlotWatch::cleanup()
{
}


