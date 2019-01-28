#ifndef REPLAYWIDGET_H
#define REPLAYWIDGET_H

#include <QWidget>

class QLabel;
class QToolButton;
class QSlider;
namespace RadarDisplay {
class ReplayRadar;
class ReplaySlider;
class ReplayWidget : public QWidget
{
    Q_OBJECT
    
public:
    ReplayWidget(ReplayRadar *radar, QWidget *parent = 0);
    ~ReplayWidget();

    void timerEvent(QTimerEvent *);

signals:
    void finished();

public slots:
    void startPauseReplay();
    void stopReplay();
    void seekBackwardReplay();
    void seekForwardReplay();
    void speedDownReplay();
    void speedUpReplay();
    void slideReplay();

    void replayStarted();
    void replayStopped();
    void replayPaused();
    void replayResumed();
    void replaySpeedChanged(qreal speed);
    void replayFileChanged(const QString &file);
    void finishReplay();

private:
    void enableReplayControls(bool enable);

    ReplayRadar *m_replayRadar;

    QLabel *m_timeLabel;
    QLabel *m_speedLabel;
    QLabel *m_statusLabel;

    ReplaySlider *m_slider;

    QToolButton *m_stopButton;
    QToolButton *m_seekBackwardButton;
    QToolButton *m_playButton;
    QToolButton *m_seekForwardButton;
    QToolButton *m_speedDownButton;
    QToolButton *m_speedUpButton;
    QToolButton *m_backButton;

    int m_timerId;
};
}

#endif // REPLAYWIDGET_H
