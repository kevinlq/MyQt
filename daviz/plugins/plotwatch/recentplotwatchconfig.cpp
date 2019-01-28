#include "recentplotwatchconfig.h"
#include "ui_recentplotwatchconfig.h"

#include <QDebug>

using namespace RadarDisplay;

static const int VALUE_COUNT = 5;
static const int VALUE_LENGTH[] = {1, 5, 10, 20, 50};

RecentPlotWatchConfig::RecentPlotWatchConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecentPlotWatchConfig)
{
    ui->setupUi(this);
    Q_ASSERT((ui->slider->minimum() == 0) && (ui->slider->maximum() == VALUE_COUNT - 1));
    connect(ui->slider, SIGNAL(valueChanged(int)), SLOT(sliderValueChanged(int)));
    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(hide()));
}

RecentPlotWatchConfig::~RecentPlotWatchConfig()
{
    delete ui;
}

int RecentPlotWatchConfig::recentLength() const
{
    return getLength(ui->slider->value());
}

void RecentPlotWatchConfig::setRecentLength(int length)
{
    ui->slider->setValue(getValue(length));
}

void RecentPlotWatchConfig::sliderValueChanged(int value)
{
    ui->label->setText(QString(tr("Recent length: <b>%1</b> ")).arg(getLength(value)));
}

int RecentPlotWatchConfig::getValue(int length) const
{
    for (int i = 0; i < VALUE_COUNT; i++)
        if (VALUE_LENGTH[i] == length)
            return i;
    return 0;
}

int RecentPlotWatchConfig::getLength(int value) const
{
    Q_ASSERT((0 <= value) && (value < VALUE_COUNT));

    return VALUE_LENGTH[value];
}
