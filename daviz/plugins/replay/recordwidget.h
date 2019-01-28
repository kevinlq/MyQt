#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include <QElapsedTimer>

class QLabel;
class QToolButton;

namespace RadarDisplay {
class Recorder;
class RecordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecordWidget(Recorder *recorder, QWidget *parent = 0);

    void timerEvent(QTimerEvent *);
    
signals:
    void finished();
    
public slots:
    void recordStarted();
    void recordStopped();
    void finishRecord();

private:
    QString prettySize(qint64 size) const;

    Recorder *m_recorder;

    QLabel *m_timeLenLabel;
    QLabel *m_fileLabel;
    QLabel *m_statusLabel;
    QToolButton *m_backButton;

    int m_timerId;
    QElapsedTimer m_time;
};
}

#endif // RECORDWIDGET_H
