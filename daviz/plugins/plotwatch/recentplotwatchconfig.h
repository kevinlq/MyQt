#ifndef RECENTPLOTWATCHCONFIG_H
#define RECENTPLOTWATCHCONFIG_H

#include <qglobal.h>
#include <QWidget>

namespace Ui {
class RecentPlotWatchConfig;
}

namespace RadarDisplay {
class RecentPlotWatchConfig : public QWidget
{
    Q_OBJECT
    
public:
    explicit RecentPlotWatchConfig(QWidget *parent = 0);
    ~RecentPlotWatchConfig();
    int recentLength() const;
    void setRecentLength(int length);

public slots:
    void sliderValueChanged(int value);
    
private:
    int getValue(int length) const;
    int getLength(int value) const;
    Ui::RecentPlotWatchConfig *ui;
};
}

#endif // RECENTPLOTWATCHCONFIG_H
