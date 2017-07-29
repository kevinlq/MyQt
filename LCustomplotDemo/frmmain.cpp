#include "frmmain.h"
#include "ui_frmmain.h"

#include <QTimer>

#define TextColor QColor(255,255,255)
#define Plot_NoColor QColor(0,0,0,0)

#define Plot1_DotColor QColor(5,189,251)
#define Plot1_LineColor QColor(41,138,220)
#define Plot1_BGColor QColor(41,138,220,80)

#define Plot2_DotColor QColor(236,110,0)
#define Plot2_LineColor QColor(246,98,0)
#define Plot2_BGColor QColor(246,98,0,80)

#define Plot3_AlarmColor1 QColor(204,0,0)
#define Plot3_AlarmColor1X QColor(204,0,0,200)
#define Plot3_AlarmColor2 QColor(246,98,0)
#define Plot3_AlarmColor2X QColor(246,98,0,200)
#define Plot3_AlarmColor3 QColor(41,138,220)
#define Plot3_AlarmColor3X QColor(41,138,220,200)

#define Plot4_AlarmColor1 QColor(238,0,0)
#define Plot4_AlarmColor1X QColor(238,0,0,200)
#define Plot4_AlarmColor2 QColor(204,250,255)
#define Plot4_AlarmColor2X QColor(204,250,255,200)
#define Plot4_AlarmColor3 QColor(5,189,251)
#define Plot4_AlarmColor3X QColor(5,189,251,200)
#define Plot4_AlarmColor4 QColor(236,110,0)
#define Plot4_AlarmColor4X QColor(236,110,0,200)
#define Plot4_AlarmColor5 QColor(106,139,34)
#define Plot4_AlarmColor5X QColor(106,139,34,200)
#define Plot4_AlarmColor6 QColor(99,149,236)
#define Plot4_AlarmColor6X QColor(99,149,236,200)
#define Plot4_AlarmColor7 QColor(130,111,255)
#define Plot4_AlarmColor7X QColor(130,111,255,200)
#define Plot4_AlarmColor8 QColor(205,173,0)
#define Plot4_AlarmColor8X QColor(205,173,0,200)
#define Plot4_AlarmColor9 QColor(1,139,0)
#define Plot4_AlarmColor9X QColor(1,139,0,200)

#define TextWidth 1
#define LineWidth 2
#define DotWidth 10

#define Plot1_Count 20
#define Plot2_Count 5
#define Plot3_Count 7
#define Plot4_Count 9
#define Plot5_Count 9

#define Plot1_MaxY 50
#define Plot2_MaxY 100
#define Plot3_MaxY 500
#define Plot4_MaxY 100

#ifdef __arm__
#define Plot5_MaxY 20
#else
#define Plot5_MaxY 50
#endif

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();

    this->InitPlot();
    this->InitPlot1();
    this->InitPlot2();
    this->InitPlot3();
    this->InitPlot4();
    this->InitPlot5();

    this->LoadPlot1();
    this->LoadPlot2();
    this->LoadPlot3();
    this->LoadPlot4();
    this->LoadPlot5();
    plot5_timer->start(0);
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::InitStyle()
{
    this->setProperty("Form", true);
}

void frmMain::InitForm()
{
    currentIndex = 0;

    //初始化随机数种子
    QTime time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);

    //初始化动态曲线定时器
    plot2_timer = new QTimer(this);
    connect(plot2_timer, SIGNAL(timeout()), this, SLOT(LoadPlot2()));

    //初始化动态柱状图定时器
    plot5_timer = new QTimer(this);
    connect(plot5_timer, SIGNAL(timeout()), this, SLOT(UpdatePlot5()));

    plots.append(ui->plot1);
    plots.append(ui->plot2);
    plots.append(ui->plot3);
    plots.append(ui->plot4);
    plots.append(ui->plot5);
}

void frmMain::InitPlot()
{
    //设置纵坐标名称
    plots[0]->yAxis->setLabel("力度值(单位:N)");
    plots[1]->yAxis->setLabel("湿度值(单位:%)");
    plots[2]->yAxis->setLabel("一周报警总数统计图");
    plots[3]->yAxis->setLabel("报警数量统计图");
    plots[4]->yAxis->setLabel("报警数量统计图");

    //设置纵坐标范围
    plots[0]->yAxis->setRange(0, Plot1_MaxY);
    plots[1]->yAxis->setRange(0, Plot2_MaxY);
    plots[2]->yAxis->setRange(0, Plot3_MaxY);
    plots[3]->yAxis->setRange(0, Plot4_MaxY);
    plots[4]->yAxis->setRange(0, Plot5_MaxY);

    foreach (QCustomPlot * plot, plots) {
        //设置坐标颜色/坐标名称颜色
        plot->yAxis->setLabelColor(TextColor);
        plot->xAxis->setTickLabelColor(TextColor);
        plot->yAxis->setTickLabelColor(TextColor);
        plot->xAxis->setBasePen(QPen(TextColor, TextWidth));
        plot->yAxis->setBasePen(QPen(TextColor, TextWidth));
        plot->xAxis->setTickPen(QPen(TextColor, TextWidth));
        plot->yAxis->setTickPen(QPen(TextColor, TextWidth));
        plot->xAxis->setSubTickPen(QPen(TextColor, TextWidth));
        plot->yAxis->setSubTickPen(QPen(TextColor, TextWidth));

        //设置画布背景色
        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(80, 80, 80));
        plotGradient.setColorAt(1, QColor(50, 50, 50));
        plot->setBackground(plotGradient);

        //设置坐标背景色
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(80, 80, 80));
        axisRectGradient.setColorAt(1, QColor(30, 30, 30));
        plot->axisRect()->setBackground(axisRectGradient);

        //设置图例提示位置及背景色
        plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);
        plot->legend->setBrush(QColor(255, 255, 255, 200));

        plot->replot();
    }
}

void frmMain::InitPlot1()
{
    plots[0]->addGraph();
    plots[0]->graph(0)->setName("力度值(单位:N)");
    plots[0]->graph(0)->setPen(QPen(Plot1_LineColor, LineWidth));
    plots[0]->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle,
                        QPen(Plot1_DotColor, LineWidth),
                        QBrush(Plot1_DotColor), DotWidth));

    //设置静态曲线的横坐标范围及自适应横坐标
    plots[0]->xAxis->setRange(0, Plot1_Count, Qt::AlignLeft);
    for (int i = 0; i < Plot1_Count; i++) {
        plot1_keys.append(i);
    }
}

void frmMain::InitPlot2()
{
    plots[1]->addGraph();
    plots[1]->graph(0)->setName("湿度值(单位:%)");
    plots[1]->graph(0)->setPen(QPen(Plot2_LineColor, LineWidth));
    plots[1]->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle,
                        QPen(Plot2_DotColor, LineWidth),
                        QBrush(Plot2_DotColor), DotWidth));

    //设置动态曲线的横坐标格式及范围
    plots[1]->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    plots[1]->xAxis->setDateTimeFormat("HH:mm:ss");
    plots[1]->xAxis->setAutoTickStep(false);
    plots[1]->xAxis->setTickStep(0.5);
    plots[1]->xAxis->setRange(0, Plot2_Count, Qt::AlignRight);
}

void frmMain::InitPlot3()
{
    //初始化横坐标名称
    plot3_labels << "星期一" << "星期二" << "星期三";
    plot3_labels << "星期四" << "星期五" << "星期六" << "星期日";

    //创建三个柱状图形对象
    for (int i = 0; i < 3; i++) {
        QCPBars *bar = new QCPBars(plots[2]->xAxis, plots[2]->yAxis);
        plot3_Bar.append(bar);
        plots[2]->addPlottable(plot3_Bar[i]);
    }

    //设置三个柱状图形对象名称
    plot3_Bar[0]->setName("极其重要警情");
    plot3_Bar[1]->setName("重要警情");
    plot3_Bar[2]->setName("一般警情");

    //分别对三个柱状图形对象设置颜色
    QPen pen;
    pen.setWidthF(LineWidth);
    pen.setColor(Plot3_AlarmColor1);
    plot3_Bar[0]->setPen(pen);
    plot3_Bar[0]->setBrush(Plot3_AlarmColor1X);
    pen.setColor(Plot3_AlarmColor2);
    plot3_Bar[1]->setPen(pen);
    plot3_Bar[1]->setBrush(Plot3_AlarmColor2X);
    pen.setColor(Plot3_AlarmColor3);
    plot3_Bar[2]->setPen(pen);
    plot3_Bar[2]->setBrush(Plot3_AlarmColor3X);

    //设置柱状图形排列次序
    plot3_Bar[1]->moveAbove(plot3_Bar[2]);
    plot3_Bar[0]->moveAbove(plot3_Bar[1]);

    //设置横坐标
    plots[2]->xAxis->setAutoTicks(false);
    plots[2]->xAxis->setAutoTickLabels(false);
    plots[2]->xAxis->setSubTickCount(0);
    plots[2]->xAxis->setTickLength(0, 4);
    plots[2]->xAxis->grid()->setVisible(false);
    plots[2]->xAxis->setRange(0, 8);
    plots[2]->yAxis->grid()->setSubGridVisible(false);

    //横坐标赋值
    plot3_keys << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    plots[2]->xAxis->setTickVector(plot3_keys);
    plots[2]->xAxis->setTickVectorLabels(plot3_labels);
}

void frmMain::InitPlot4()
{
    //初始化横坐标名称
    plot4_labels << "水量超限报警" << "缺水报警" << "无传感器" << "温度过高" << "温度过低" ;
    plot4_labels << "湿度过高" << "湿度过低" << "环境温度过低" << "温度超限停机";

    //初始化纵坐标值/柱状对象
    for (int i = 0; i < Plot4_Count; i++) {
        plot4_values.append(0);
        plot4_keys.append(i + 1);
        QCPBars *bar = new QCPBars(plots[3]->xAxis, plots[3]->yAxis);
        bar->setName(plot4_labels[i]);
        plots[3]->addPlottable(bar);
        plot4_Bar.append(bar);
    }

    //设置柱状图形颜色
    QPen pen;
    pen.setWidthF(LineWidth);
    pen.setColor(Plot4_AlarmColor1);
    plot4_Bar[0]->setPen(pen);
    plot4_Bar[0]->setBrush(Plot4_AlarmColor1X);
    pen.setColor(Plot4_AlarmColor2);
    plot4_Bar[1]->setPen(pen);
    plot4_Bar[1]->setBrush(Plot4_AlarmColor2X);
    pen.setColor(Plot4_AlarmColor3);
    plot4_Bar[2]->setPen(pen);
    plot4_Bar[2]->setBrush(Plot4_AlarmColor3X);
    pen.setColor(Plot4_AlarmColor4);
    plot4_Bar[3]->setPen(pen);
    plot4_Bar[3]->setBrush(Plot4_AlarmColor4X);
    pen.setColor(Plot4_AlarmColor5);
    plot4_Bar[4]->setPen(pen);
    plot4_Bar[4]->setBrush(Plot4_AlarmColor5X);
    pen.setColor(Plot4_AlarmColor6);
    plot4_Bar[5]->setPen(pen);
    plot4_Bar[5]->setBrush(Plot4_AlarmColor6X);
    pen.setColor(Plot4_AlarmColor7);
    plot4_Bar[6]->setPen(pen);
    plot4_Bar[6]->setBrush(Plot4_AlarmColor7X);
    pen.setColor(Plot4_AlarmColor8);
    plot4_Bar[7]->setPen(pen);
    plot4_Bar[7]->setBrush(Plot4_AlarmColor8X);
    pen.setColor(Plot4_AlarmColor9);
    plot4_Bar[8]->setPen(pen);
    plot4_Bar[8]->setBrush(Plot4_AlarmColor9X);

    //设置横坐标
    plots[3]->xAxis->setAutoTicks(false);
    plots[3]->xAxis->setAutoTickLabels(false);
    plots[3]->xAxis->setSubTickCount(0);
    plots[3]->xAxis->grid()->setVisible(false);
    plots[3]->xAxis->setRange(0, Plot4_Count + 1);

    //横坐标赋值
    plots[3]->xAxis->setTickVector(plot4_keys);
    plots[3]->xAxis->setTickVectorLabels(plot4_labels);
}

void frmMain::InitPlot5()
{
    maxValue = 0;
    //初始化横坐标名称
    plot5_labels << "水量超限报警" << "缺水报警" << "无传感器" << "温度过高" << "温度过低" ;
    plot5_labels << "湿度过高" << "湿度过低" << "环境温度过低" << "温度超限停机";

    //初始化纵坐标值/柱状对象
    for (int i = 0; i < Plot5_Count; i++) {
        plot5_values.append(0);
        plot5_keys.append(i + 1);
        QCPBars *bar = new QCPBars(plots[4]->xAxis, plots[4]->yAxis);
        bar->setName(plot5_labels[i]);
        plots[4]->addPlottable(bar);
        plot5_Bar.append(bar);
    }

    //设置柱状图形颜色
    QPen pen;
    pen.setWidthF(LineWidth);
    pen.setColor(Plot4_AlarmColor1);
    plot5_Bar[0]->setPen(pen);
    plot5_Bar[0]->setBrush(Plot4_AlarmColor1X);
    pen.setColor(Plot4_AlarmColor2);
    plot5_Bar[1]->setPen(pen);
    plot5_Bar[1]->setBrush(Plot4_AlarmColor2X);
    pen.setColor(Plot4_AlarmColor3);
    plot5_Bar[2]->setPen(pen);
    plot5_Bar[2]->setBrush(Plot4_AlarmColor3X);
    pen.setColor(Plot4_AlarmColor4);
    plot5_Bar[3]->setPen(pen);
    plot5_Bar[3]->setBrush(Plot4_AlarmColor4X);
    pen.setColor(Plot4_AlarmColor5);
    plot5_Bar[4]->setPen(pen);
    plot5_Bar[4]->setBrush(Plot4_AlarmColor5X);
    pen.setColor(Plot4_AlarmColor6);
    plot5_Bar[5]->setPen(pen);
    plot5_Bar[5]->setBrush(Plot4_AlarmColor6X);
    pen.setColor(Plot4_AlarmColor7);
    plot5_Bar[6]->setPen(pen);
    plot5_Bar[6]->setBrush(Plot4_AlarmColor7X);
    pen.setColor(Plot4_AlarmColor8);
    plot5_Bar[7]->setPen(pen);
    plot5_Bar[7]->setBrush(Plot4_AlarmColor8X);
    pen.setColor(Plot4_AlarmColor9);
    plot5_Bar[8]->setPen(pen);
    plot5_Bar[8]->setBrush(Plot4_AlarmColor9X);

    //设置横坐标
    plots[4]->xAxis->setAutoTicks(false);
    plots[4]->xAxis->setAutoTickLabels(false);
    plots[4]->xAxis->setSubTickCount(0);
    plots[4]->xAxis->grid()->setVisible(false);
    plots[4]->xAxis->setRange(0, Plot5_Count + 1);

    //横坐标赋值
    plots[4]->xAxis->setTickVector(plot5_keys);
    plots[4]->xAxis->setTickVectorLabels(plot5_labels);
}

void frmMain::LoadPlot1()
{
    plot1_values.clear();
    for (int i = 0; i < Plot1_Count; i++) {
        double value = qrand() % Plot1_MaxY;
        plot1_values.append(value);
    }
    plots[0]->graph(0)->setData(plot1_keys, plot1_values);
    plots[0]->graph(0)->rescaleAxes();
    plots[0]->replot();
}

void frmMain::LoadPlot2()
{
    plot2_key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    plot2_value = qrand() % Plot2_MaxY;
    plots[1]->graph(0)->addData(plot2_key, plot2_value);
    plots[1]->graph(0)->removeDataBefore(plot2_key - Plot2_Count - 1);
    plots[1]->xAxis->setRange(plot2_key, Plot2_Count , Qt::AlignRight);
    plots[1]->replot();
}

void frmMain::LoadPlot3()
{
    plot3_values1.clear();
    plot3_values2.clear();
    plot3_values3.clear();
    for (int i = 0; i < 10; i++) {
        double value1 = qrand() % 80;
        double value2 = qrand() % 100;
        double value3 = qrand() % 300;
        plot3_values1.append(value1);
        plot3_values2.append(value2);
        plot3_values3.append(value3);
    }

    //设置柱状图形数据
    plot3_Bar[0]->setData(plot3_keys, plot3_values1);
    plot3_Bar[1]->setData(plot3_keys, plot3_values2);
    plot3_Bar[2]->setData(plot3_keys, plot3_values3);
    plots[2]->replot();
}

void frmMain::LoadPlot4()
{
    plot4_values.clear();
    for (int i = 0; i < Plot4_Count; i++) {
        double value = qrand() % (Plot4_MaxY - 10);
        plot4_values.append(value);
        plot4_Bar[i]->clearData();
        plot4_Bar[i]->addData(i + 1, plot4_values[i]);
    }
    plots[3]->replot();
}

void frmMain::LoadPlot5()
{
    maxValue = 0;
    plot5_currentValue.clear();
    plot5_values.clear();
    for (int i = 0; i < Plot5_Count; i++) {
        double value = qrand() % (Plot5_MaxY - 1);
        plot5_currentValue.append(0);
        plot5_values.append(value);
    }
}

void frmMain::UpdatePlot5()
{
    for (int i = 0; i < Plot5_Count; i++) {
        if (plot5_currentValue[i] < plot5_values[i]) {
            plot5_Bar[i]->clearData();
            plot5_Bar[i]->addData(i + 1, plot5_currentValue[i]);
            plot5_currentValue[i]++;
        }
    }

    maxValue++;
    plots[4]->replot();

    if (maxValue >= (Plot5_MaxY - 1)) {
        maxValue = 0;
        plot5_timer->stop();
    }
}

void frmMain::on_btnLoad_clicked()
{
#if 0
    if (currentIndex == 0) {
        LoadPlot1();
    } else if (currentIndex == 1) {
        if (ui->btnLoad->text() == "开始模拟") {
            plot2_timer->start(100);
            ui->btnLoad->setText("停止模拟");
        } else {
            plot2_timer->stop();
            ui->btnLoad->setText("开始模拟");
        }
    } else if (currentIndex == 2) {
        LoadPlot3();
    } else if (currentIndex == 3) {
        LoadPlot4();
    } else if (currentIndex == 4) {
        LoadPlot5();
        //启动定时器动态加载柱状条
        plot5_timer->start(0);
    }
#endif
}



void frmMain::on_ckText_stateChanged(int arg1)
{
    bool value = (arg1 == 0 ? false : true);
    if (value) {
        plots[0]->legend->setVisible(true);
        plots[1]->legend->setVisible(true);
        plots[2]->legend->setVisible(true);
        plots[3]->legend->setVisible(true);
        plots[4]->legend->setVisible(true);
    } else {
        plots[0]->legend->setVisible(false);
        plots[1]->legend->setVisible(false);
        plots[2]->legend->setVisible(false);
        plots[3]->legend->setVisible(false);
        plots[4]->legend->setVisible(false);
    }

    foreach (QCustomPlot * plot, plots) {
        plot->replot();
    }
}

void frmMain::on_ckBackground_stateChanged(int arg1)
{
    bool value = (arg1 == 0 ? false : true);
    if (value) {
        plots[0]->graph(0)->setBrush(QBrush(Plot1_BGColor));
        plots[1]->graph(0)->setBrush(QBrush(Plot2_BGColor));
    } else {
        plots[0]->graph(0)->setBrush(QBrush(Plot_NoColor));
        plots[1]->graph(0)->setBrush(QBrush(Plot_NoColor));
    }
    plots[0]->replot();
    plots[1]->replot();
}

void frmMain::on_ckMove_stateChanged(int arg1)
{
    bool value = (arg1 == 0 ? false : true);
    if (value) {
        ui->plot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->plot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->plot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->plot4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->plot5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    } else {
        ui->plot1->setInteractions(QCP::iSelectOther);
        ui->plot2->setInteractions(QCP::iSelectOther);
        ui->plot3->setInteractions(QCP::iSelectOther);
        ui->plot4->setInteractions(QCP::iSelectOther);
        ui->plot5->setInteractions(QCP::iSelectOther);
    }
}

void frmMain::on_tabWidget_currentChanged(int index)
{
    currentIndex = index;
    plot2_timer->stop();
    plot5_timer->stop();
    maxValue = 0;

    ui->plot2->graph(0)->clearData();
    ui->plot2->replot();
}
