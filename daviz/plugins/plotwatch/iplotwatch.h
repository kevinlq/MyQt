#ifndef IPLOTWATCH_H
#define IPLOTWATCH_H

#include "plotwatch_global.h"
#include "core/icore.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets/QtWidgets>
#else
#include <QWidget>
#include <QIcon>
#include <QString>
#endif

namespace RadarDisplay {
class IRadar;
class PLOTWATCH_EXPORT IPlotWatch : public QObject
{
    Q_OBJECT
public:
    enum Ability {
        NoAbility = 0,
        PauseResumeAbility = 1,
        ClearAbility = 2,
        ConfigAbility = 4
    };
    Q_DECLARE_FLAGS(Abilities, Ability)

    enum State {
        Running = 1,
        Paused
    };

    explicit IPlotWatch(QObject *parent = 0);
    virtual ~IPlotWatch() ;

    Abilities abilities() const;
    void setAbilities(Abilities abilities);

    State state() const;
    void setState(State _state);

    QIcon icon() const;
    void setIcon(const QIcon &_icon);
    QString text() const;
    void setText(const QString &_text);
    QWidget *widget() const;
    void setWidget(QWidget *widget);

    virtual void plotRemoveAll();

    virtual void plotAdded(const PlotData &plot);
    virtual void antennaPositionChanged(float degree);
    virtual void pause();
    virtual void resume();
    virtual void clear();
    virtual void config();
    virtual void cleanup();

signals:
    
public slots:
    
private:
    QIcon m_icon;
    QString m_text;
    QWidget *m_widget;
    Abilities m_abilities;
    State m_state;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(IPlotWatch::Abilities)
}
#endif // IPLOTWATCH_H
