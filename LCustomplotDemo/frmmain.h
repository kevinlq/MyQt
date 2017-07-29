#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui
{
    class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

private slots:
    void LoadPlot1();
    void LoadPlot2();
    void LoadPlot3();
    void LoadPlot4();
    void LoadPlot5();
    void UpdatePlot5();

private:
    Ui::frmMain *ui;

    QTimer *plot2_timer;
    QTimer *plot5_timer;

    int currentIndex;
    QString currentSkin;
    QList <QCustomPlot *> plots;

    QVector<double> plot1_keys;
    QVector<double> plot1_values;

    double plot2_key;
    double plot2_value;

    QVector<double> plot3_keys;
    QVector<double> plot3_values1, plot3_values2, plot3_values3;
    QVector<QString> plot3_labels;
    QVector<QCPBars *> plot3_Bar;

    QVector<double> plot4_keys;
    QVector<double> plot4_values;
    QVector<QString> plot4_labels;
    QVector<QCPBars *> plot4_Bar;

    QVector<double> plot5_keys;
    QVector<double> plot5_values;
    QVector<double> plot5_currentValue;
    int maxValue;
    QVector<QString> plot5_labels;
    QVector<QCPBars *> plot5_Bar;

    void InitStyle();
    void InitForm();

    void InitPlot();
    void InitPlot1();
    void InitPlot2();
    void InitPlot3();
    void InitPlot4();
    void InitPlot5();

};

#endif // FRMMAIN_H
