#include "replaywidget.h"
#include "replayconstants.h"
#include "replayradar.h"
#include "replayslider.h"
#include <QSlider>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

using namespace RadarDisplay;

ReplayWidget::ReplayWidget(ReplayRadar *radar, QWidget *parent) :
    QWidget(parent),
    m_replayRadar(radar),
    m_timerId(0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    {
        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->setSpacing(0);

        m_timeLabel = new QLabel(this);
        m_timeLabel->setText(QStringLiteral("00:00:00"));
        m_timeLabel->setFixedWidth(120);
        hlayout->addWidget(m_timeLabel);

        //        hlayout->addSpacing(40);

        m_speedLabel = new QLabel(this);
        m_speedLabel->setText(QStringLiteral("1.0x"));
        hlayout->addWidget(m_speedLabel);

        hlayout->addStretch(1);

        m_statusLabel = new QLabel(this);
        m_statusLabel->setText("playing");
        m_statusLabel->setAlignment(Qt::AlignRight);
        hlayout->addWidget(m_statusLabel);

        layout->addLayout(hlayout);
    }

    m_slider = new ReplaySlider(Qt::Horizontal, this);
    m_slider->setRange(0, 1000);
    m_slider->setTracking(false);
    m_slider->setPageStep(100);
    layout->addWidget(m_slider);

    {
        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->setSpacing(0);

        m_stopButton = new QToolButton(this);
        m_stopButton->setAutoRaise(true);
        m_stopButton->setIcon(QIcon(":/icons/media-playback-stop.png"));
        hlayout->addWidget(m_stopButton);

        m_seekBackwardButton = new QToolButton(this);
        m_seekBackwardButton->setAutoRaise(true);
        m_seekBackwardButton->setIcon(QIcon(":/icons/media-skip-backward.png"));
        hlayout->addWidget(m_seekBackwardButton);

        m_playButton = new QToolButton(this);
        m_playButton->setAutoRaise(true);
        m_playButton->setIcon(QIcon(":/icons/media-playback-start.png"));
        hlayout->addWidget(m_playButton);

        m_seekForwardButton = new QToolButton(this);
        m_seekForwardButton->setAutoRaise(true);
        m_seekForwardButton->setIcon(QIcon(":/icons/media-skip-forward.png"));
        hlayout->addWidget(m_seekForwardButton);

        hlayout->addSpacing(20);

        m_speedDownButton = new QToolButton(this);
        m_speedDownButton->setAutoRaise(true);
        m_speedDownButton->setIcon(QIcon(":/icons/media-seek-backward.png"));
        hlayout->addWidget(m_speedDownButton);

        m_speedUpButton = new QToolButton(this);
        m_speedUpButton->setAutoRaise(true);
        m_speedUpButton->setIcon(QIcon(":/icons/media-seek-forward.png"));
        hlayout->addWidget(m_speedUpButton);

        hlayout->addStretch(1);

        m_backButton = new QToolButton(this);
        m_backButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //        backButton->setAutoRaise(true);
        m_backButton->setIcon(QIcon(":/icons/arrow-left.png"));
        m_backButton->setText("back");
        hlayout->addWidget(m_backButton);

        layout->addLayout(hlayout);
    }

    connect(m_replayRadar, SIGNAL(started()), SLOT(replayStarted()));
    connect(m_replayRadar, SIGNAL(stopped()), SLOT(replayStopped()));
    connect(m_replayRadar, SIGNAL(paused()), SLOT(replayPaused()));
    connect(m_replayRadar, SIGNAL(resumed()), SLOT(replayResumed()));
    connect(m_replayRadar, SIGNAL(speedChanged(qreal)), SLOT(replaySpeedChanged(qreal)));
    connect(m_replayRadar, SIGNAL(replayFileChanged(QString)), SLOT(replayFileChanged(QString)));

    connect(m_stopButton, SIGNAL(clicked()), SLOT(stopReplay()));
    connect(m_seekBackwardButton, SIGNAL(clicked()), SLOT(seekBackwardReplay()));
    connect(m_playButton, SIGNAL(clicked()), SLOT(startPauseReplay()));
    connect(m_seekForwardButton, SIGNAL(clicked()), SLOT(seekForwardReplay()));
    connect(m_speedDownButton, SIGNAL(clicked()), SLOT(speedDownReplay()));
    connect(m_speedUpButton, SIGNAL(clicked()), SLOT(speedUpReplay()));
    //    connect(m_slider, SIGNAL(sliderReleased()), SLOT(slideReplay()));
    connect(m_slider, SIGNAL(valueChanged(int)), SLOT(slideReplay()));

    connect(m_stopButton, SIGNAL(clicked()), SLOT(stopReplay()));
    connect(m_backButton, SIGNAL(clicked()), SLOT(finishReplay()));
}

ReplayWidget::~ReplayWidget()
{
    
}

void ReplayWidget::timerEvent(QTimerEvent *)
{
    qint64 n = m_replayRadar->msecsTotal();
    qint64 cur = m_replayRadar->msecsElapsed();
    if (n > 0 && cur >= 0 && cur <= n) {
        qreal playedPercent = 100 * (qreal)cur / n;
        QString timeText = QString("%1 (%2%)")
                .arg(m_replayRadar->currentTime().toString("hh:mm:ss"))
                .arg(playedPercent, 0, 'f', 0);
        m_timeLabel->setText(timeText);
        int pos = cur * m_slider->maximum() / n;
        if (!m_slider->isSliderDown()) {
            m_slider->blockSignals(true);
            m_slider->setSliderPosition(pos);
            m_slider->blockSignals(false);
        }
    } else if (n == 0) {
        QString timeText = QString("%1 (%2%%)")
                .arg(m_replayRadar->currentTime().toString("hh:mm:ss"))
                .arg(100.0, 0, 'f', 0);
        m_timeLabel->setText(timeText);
        if (!m_slider->isSliderDown()) {
            m_slider->blockSignals(true);
            m_slider->setSliderPosition(m_slider->maximum());
            m_slider->blockSignals(false);
        }
    }
}

void ReplayWidget::finishReplay()
{
    emit finished();
}

void ReplayWidget::enableReplayControls(bool enable)
{
    m_timeLabel->setText("00:00:00");
    m_timeLabel->setEnabled(enable);
    m_speedLabel->setText("1.00x");
    m_speedLabel->setEnabled(enable);
//    m_statusLabel->setEnabled(enable);
    m_slider->setEnabled(enable);
    m_stopButton->setEnabled(enable);
    m_seekBackwardButton->setEnabled(enable);
//    m_playButton->setEnabled(enable);
    m_seekForwardButton->setEnabled(enable);
    m_speedDownButton->setEnabled(enable);
    m_speedUpButton->setEnabled(enable);
}

void ReplayWidget::replayStarted()
{
    enableReplayControls(true);

    m_statusLabel->setText("Running");
    m_slider->setSliderPosition(0);
    m_playButton->setIcon(QIcon(":/icons/media-playback-pause.png"));
    Q_ASSERT(m_timerId == 0);
    m_timerId = startTimer(50);
}

void ReplayWidget::replayStopped()
{
    enableReplayControls(false);

    m_statusLabel->setText("Stopped");
    m_slider->setSliderPosition(0);
    m_playButton->setIcon(QIcon(":/icons/media-playback-start.png"));
    if (m_timerId) {
        killTimer(m_timerId);
        m_timerId = 0;
    }
}

void ReplayWidget::replayPaused()
{
    m_statusLabel->setText("Paused");
    m_playButton->setIcon(QIcon(":/icons/media-playback-start.png"));
    if (m_timerId) {
        killTimer(m_timerId);
        m_timerId = 0;
    }
}

void ReplayWidget::replayResumed()
{
    m_statusLabel->setText("Running");
    m_playButton->setIcon(QIcon(":/icons/media-playback-pause.png"));
    Q_ASSERT(m_timerId == 0);
    m_timerId = startTimer(50);
}

void ReplayWidget::replaySpeedChanged(qreal speed)
{
    m_speedLabel->setText(QString("%1x").arg(speed, 0, 'f', 2));
}

void ReplayWidget::replayFileChanged(const QString &file)
{
    Q_UNUSED(file)
}

void ReplayWidget::startPauseReplay()
{
    if (m_replayRadar->isStopped())
        m_replayRadar->start();
    else if (m_replayRadar->isRunning())
        m_replayRadar->pause();
    else if (m_replayRadar->isPaused())
        m_replayRadar->resume();
    else
        Q_ASSERT(0);
}

void ReplayWidget::stopReplay()
{
    m_replayRadar->stop();
}

void ReplayWidget::seekBackwardReplay()
{
    m_replayRadar->advanceMSecs(-10*1000);
}

void ReplayWidget::seekForwardReplay()
{
    m_replayRadar->advanceMSecs(10*1000);
}

void ReplayWidget::speedDownReplay()
{
    qreal speed = m_replayRadar->speed();
    if (speed > 0.25) {
        speed -= 0.25;
        m_replayRadar->setSpeed(speed);
    }
}

void ReplayWidget::speedUpReplay()
{
    qreal speed = m_replayRadar->speed();
    if (speed < 4.0) {
        speed += 0.25;
        m_replayRadar->setSpeed(speed);
    }
}

void ReplayWidget::slideReplay()
{
    int value = m_slider->sliderPosition();
    qint64 msec = value * m_replayRadar->msecsTotal() / m_slider->maximum();
    m_replayRadar->advanceMSecs(msec - m_replayRadar->msecsElapsed());
}
