#include "recordwidget.h"
#include "recorder.h"
#include "replayconstants.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QCoreApplication>
#include <QTime>
#include <QDebug>

using namespace RadarDisplay;
RecordWidget::RecordWidget(Recorder *recorder, QWidget *parent) :
    QWidget(parent),
    m_recorder(recorder),
    m_timerId(0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    {
        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->setSpacing(0);

        m_timeLenLabel = new QLabel(this);
        m_timeLenLabel->setText("00:00:00");
        m_timeLenLabel->setFixedWidth(120);
        hlayout->addWidget(m_timeLenLabel);

//        hlayout->addSpacing(20);

        hlayout->addStretch(1);

        m_statusLabel = new QLabel(this);
        m_statusLabel->setText("recording");
        hlayout->addWidget(m_statusLabel);

        layout->addLayout(hlayout);
    }
    {
        QHBoxLayout *hlayout = new QHBoxLayout;
        hlayout->setSpacing(0);

        m_fileLabel = new QLabel(this);
        m_fileLabel->setText("a.txt");
        hlayout->addWidget(m_fileLabel);

        hlayout->addStretch(1);

        m_backButton = new QToolButton(this);
        m_backButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        m_backButton->setIcon(QIcon(":/icons/arrow-left.png"));
        m_backButton->setText("back");
        hlayout->addWidget(m_backButton);

        layout->addLayout(hlayout);
    }

    connect(m_recorder, SIGNAL(started()), SLOT(recordStarted()));
    connect(m_recorder, SIGNAL(stopped()), SLOT(recordStopped()));
    connect(m_backButton, SIGNAL(clicked()), SLOT(finishRecord()));
}

void RecordWidget::timerEvent(QTimerEvent *)
{
    QTime t(0, 0, 0, 0);
    t = t.addMSecs(m_time.elapsed());
    m_timeLenLabel->setText(t.toString("hh:mm:ss"));
    QDir replayDir(qApp->applicationDirPath());
    replayDir.cd(REPLAY_DIR_NAME);
    QFileInfo fi(replayDir, m_recorder->currentFileName());
    m_fileLabel->setText(QString("%1 (%2)").arg(fi.fileName()).arg(prettySize(fi.size())));
}

void RecordWidget::finishRecord()
{
    m_recorder->stop();
    emit finished();
}

QString RecordWidget::prettySize(qint64 size) const
{
    Q_ASSERT(size >= 0);
    if (size < 1024)
        return QString("%1B").arg(size);
    else if (size < 1024 * 1024)
        return QString("%1KB").arg(size/1024.0, 0, 'f', 2, '0');
    else
        return QString("%1MB").arg(size/1024.0/1024.0, 0, 'f', 2, '0');
}

void RecordWidget::recordStarted()
{
    m_statusLabel->setText(tr("Recording"));
    m_fileLabel->setText(m_recorder->currentFileName());
    Q_ASSERT(m_timerId == 0);
    m_timerId = startTimer(1000);
    m_time.restart();
}

void RecordWidget::recordStopped()
{
    m_statusLabel->setText(tr("Stopped"));
    if (m_timerId) {
        killTimer(m_timerId);
        m_timerId = 0;
    }
    m_time = QElapsedTimer();
}
