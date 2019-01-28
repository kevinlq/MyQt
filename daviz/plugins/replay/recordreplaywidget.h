#ifndef RECORDREPLAYWIDGET_H
#define RECORDREPLAYWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QDate>

class QToolButton;
class QStackedLayout;
class QListWidget;
class QDateEdit;
namespace RadarDisplay {
class Recorder;
class ReplayRadar;
class ReplayWidget;
class RecordWidget;
class IRadar;
class RecordReplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecordReplayWidget(Recorder *recorder, ReplayRadar *radar, QWidget *parent = 0);
    
    static QStringList availableReplayFiles();

signals:
    
public slots:
    void currentRadarChanged(IRadar *radar);
    void replayFileSelected(const QString &replayFile);
    void refreshReplayList();
    void filterByDate(const QDate &date);
    void exportReplay();
    void toReplayMode();
    void toRecordMode();
    void replayFinished();
    void recordFinished();
    
private:
    bool inPanel() const;
    void adjustPanelSize();

    Recorder *m_recorder;
    ReplayRadar *m_replayRadar;

    QWidget *m_baseWidget;
    QStackedLayout *m_stackLayout;

    QListWidget *m_listWidget;
    QToolButton *m_refreshButton;
    QDateEdit *m_dateEdit;
    QToolButton *m_exportButton;
    QToolButton *m_replayButton;
    QToolButton *m_recordButton;

    ReplayWidget *m_replayWidget;
    RecordWidget *m_recordWidget;

    QStringList m_replayFiles;
};
}

#endif // RECORDREPLAYWIDGET_H
