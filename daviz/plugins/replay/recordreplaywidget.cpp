#include "recordreplaywidget.h"
#include "recordwidget.h"
#include "replaywidget.h"
#include "replayconstants.h"
#include "recorder.h"
#include "replayradar.h"
#include "panelgroup.h"
#include "panelwidget.h"
#include "icore.h"
#include "utils/separatorwidget.h"
#include <QTextCharFormat>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QListWidget>
#include <QDateEdit>
#include <QStackedLayout>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

using namespace RadarDisplay;

RecordReplayWidget::RecordReplayWidget(Recorder *recorder, ReplayRadar *radar, QWidget *parent) :
    QWidget(parent),
    m_recorder(recorder),
    m_replayRadar(radar)
{
    m_stackLayout = new QStackedLayout(this);

    m_baseWidget = new QWidget(this);
    {
        QVBoxLayout *layout = new QVBoxLayout(m_baseWidget);

        m_listWidget = new QListWidget(m_baseWidget);
        layout->addWidget(m_listWidget);

        {
            QHBoxLayout *hlayout = new QHBoxLayout;
            hlayout->setSpacing(0);

            m_refreshButton = new QToolButton(this);
            m_refreshButton->setIcon(QIcon(":/icons/view-refresh.png"));
            hlayout->addWidget(m_refreshButton);

            m_dateEdit = new QDateEdit(QDate::currentDate(), this);
            m_dateEdit->setCalendarPopup(true);
            hlayout->addWidget(m_dateEdit);

            hlayout->addWidget(new SeparatorWidget(Qt::Vertical, this));

            m_exportButton = new QToolButton(this);
            m_exportButton->setIcon(QIcon(":/icons/document-save.png"));
            m_exportButton->setEnabled(false);
            hlayout->addWidget(m_exportButton);

            m_replayButton = new QToolButton(this);
            m_replayButton->setIcon(QIcon(":/icons/media-playback-start.png"));
            m_replayButton->setEnabled(false);
            hlayout->addWidget(m_replayButton);

            hlayout->addStretch(1);

            m_recordButton = new QToolButton(this);
            m_recordButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            m_recordButton->setIcon(QIcon(":/icons/media-record.png"));
            m_recordButton->setText("record new");
            hlayout->addWidget(m_recordButton);

            layout->addLayout(hlayout);
        }

        layout->setContentsMargins(0, 0, 0, 0);
    }
    m_stackLayout->addWidget(m_baseWidget);

    m_recordWidget = new RecordWidget(recorder, this);
    m_stackLayout->addWidget(m_recordWidget);

    m_replayWidget = new ReplayWidget(radar, this);
    m_stackLayout->addWidget(m_replayWidget);

    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)), SLOT(currentRadarChanged(IRadar*)));

    connect(m_listWidget, SIGNAL(currentTextChanged(QString)), SLOT(replayFileSelected(QString)));

    connect(m_refreshButton, SIGNAL(clicked()), SLOT(refreshReplayList()));
    connect(m_dateEdit, SIGNAL(dateChanged(QDate)), SLOT(filterByDate(QDate)));

    connect(m_exportButton, SIGNAL(clicked()), SLOT(exportReplay()));
    connect(m_replayButton, SIGNAL(clicked()), SLOT(toReplayMode()));
    connect(m_recordButton, SIGNAL(clicked()), SLOT(toRecordMode()));

    connect(m_recordWidget, SIGNAL(finished()), SLOT(recordFinished()));
    connect(m_replayWidget, SIGNAL(finished()), SLOT(replayFinished()));

    refreshReplayList();
}

QStringList RecordReplayWidget::availableReplayFiles()
{
    if (!ICore::currentRadar())
        return QStringList();
    QString replayDir = QString("%1/%2").arg(qApp->applicationDirPath()).arg(REPLAY_DIR_NAME);
    QString filter = QString("%1.*.dat").arg(ICore::currentRadar()->id());
    QDir d(replayDir, filter);
    return d.entryList();
}

void RecordReplayWidget::currentRadarChanged(IRadar *radar)
{
    if (m_stackLayout->currentWidget() == m_recordWidget) {
        m_recorder->stop();
        m_stackLayout->setCurrentWidget(m_baseWidget);
    }
    if (m_stackLayout->currentWidget() == m_replayWidget && radar != m_replayRadar) {
        m_replayRadar->stop();
        m_stackLayout->setCurrentWidget(m_baseWidget);
    }
    refreshReplayList();
    filterByDate(m_dateEdit->date());
}

void RecordReplayWidget::replayFileSelected(const QString &replayFile)
{
    if (replayFile.isNull()) {
        m_exportButton->setEnabled(false);
        m_replayButton->setEnabled(false);
    } else {
        m_exportButton->setEnabled(true);
        m_replayButton->setEnabled(true);
    }
}

void RecordReplayWidget::refreshReplayList()
{
    m_listWidget->clear();

    QRegularExpression dateRX("(\\d{4}-\\d{2}-\\d{2})_");
    QRegularExpression timeRX("_(\\d{2}h\\d{2}m\\d{2}s)");
    m_replayFiles = availableReplayFiles();
    QSet<QDate> usedDates;
    foreach (const QString &replayFile, m_replayFiles) {
        QRegularExpressionMatch dateMatch = dateRX.match(replayFile);
        if (!dateMatch.hasMatch())
            continue;
        QDate startDate = QDate::fromString(dateMatch.captured(1), "yyyy-MM-dd");
        if (!startDate.isValid())
            continue;
        usedDates.insert(startDate);

        QRegularExpressionMatch timeMatch = timeRX.match(replayFile);
        if (!timeMatch.hasMatch())
            continue;
        QTime startTime = QTime::fromString(timeMatch.captured(1), "hh'h'mm'm'ss's'");
        if (!startTime.isValid())
            continue;

        QDir replayDir(QString("%1/%2").arg(qApp->applicationDirPath()).arg(REPLAY_DIR_NAME));
        QFileInfo fi(replayDir, replayFile);
        QTime endTime = fi.lastModified().time();

        QListWidgetItem *item = new QListWidgetItem(QString(tr("%1 to %2"))
                                                    .arg(startTime.toString("hh:mm:ss"))
                                                    .arg(endTime.toString("hh:mm:ss")));
        item->setData(Qt::UserRole, replayFile);
        item->setData(Qt::UserRole + 1, startDate);
        m_listWidget->addItem(item);
    }

    m_dateEdit->calendarWidget()->setDateTextFormat(QDate(), QTextCharFormat());
    QTextCharFormat tf;
    tf.setBackground(Qt::green);
    foreach (const QDate &date, usedDates) {
        m_dateEdit->calendarWidget()->setDateTextFormat(date, tf);
    }

    filterByDate(m_dateEdit->date());
}

void RecordReplayWidget::filterByDate(const QDate &date)
{
    int selectIndex = 0;
    for (int i = 0; i < m_listWidget->count(); i++) {
        QListWidgetItem *item = m_listWidget->item(i);
        QDate itemDate = item->data(Qt::UserRole + 1).toDate();
        if (itemDate == date) {
            item->setHidden(false);
            if (!selectIndex)
                selectIndex = i;
        } else
            item->setHidden(true);
    }

    m_listWidget->setCurrentRow(selectIndex);
}

void RecordReplayWidget::exportReplay()
{
    if (!m_listWidget->currentItem())
        return;
    QMessageBox::information(this, "Export replay", m_listWidget->currentItem()->text());
}

void RecordReplayWidget::toReplayMode()
{
    m_stackLayout->setCurrentWidget(m_replayWidget);
    if (inPanel()) {
        setMinimumHeight(m_recordWidget->minimumSizeHint().height());
        adjustPanelSize();
    }
    QString replayFile = m_listWidget->currentItem()->data(Qt::UserRole).toString();
    Q_ASSERT(ICore::currentRadar() != m_replayRadar);
    m_replayRadar->setBaseRadar(ICore::currentRadar());
    ICore::setCurrentRadar(m_replayRadar);
    m_replayRadar->setReplayFile(replayFile);
    m_replayRadar->start();
}

void RecordReplayWidget::toRecordMode()
{
    m_stackLayout->setCurrentWidget(m_recordWidget);
    if (inPanel()) {
        setMinimumHeight(m_recordWidget->minimumSizeHint().height());
        adjustPanelSize();
    }
    m_recorder->start();
}

void RecordReplayWidget::replayFinished()
{
    m_stackLayout->setCurrentWidget(m_baseWidget);
    if (ICore::currentRadar() == m_replayRadar)
        ICore::setCurrentRadar(m_replayRadar->baseRadar());
}

void RecordReplayWidget::recordFinished()
{
    m_stackLayout->setCurrentWidget(m_baseWidget);
    refreshReplayList();
    if (inPanel()) {
        setMinimumHeight(m_baseWidget->minimumSizeHint().height());
        adjustPanelSize();
    }
}

bool RecordReplayWidget::inPanel() const
{
    if (!parentWidget())
        return false;
    PanelWidget *panel = qobject_cast<PanelWidget *>(parentWidget());
    return (panel != 0);
}

void RecordReplayWidget::adjustPanelSize()
{
    PanelWidget *panel = qobject_cast<PanelWidget *>(parentWidget());
    if (!panel)
        return;
    if (!m_stackLayout->currentWidget())
        return;
    int height = m_stackLayout->currentWidget()->minimumSizeHint().height();
    if (height == QWIDGETSIZE_MAX)
        return;
    panel->adjustSize(height);
}
