#include "widget.h"
#include "ui_widget.h"

#include <QWebView>
#include <QWebFrame>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    initMap();
}

void Widget::initMap()
{
    QString mapPath = "file:///" + QApplication::applicationDirPath();
    ui->webView->load(mapPath + "/map.html");
    ui->webView->setContentsMargins(0,0,0,0);
    ui->webView->setTextSizeMultiplier(0.8);

    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(slotPopulateJavaScriptWindowObject()));
}

void Widget::addMarker(const QString &lot, const QString &lat,
                        const QString &micon)
{
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString marker = QString("addMarker(\"%1\",\"%2\",\"%3\")").arg(lot).arg(lat).arg(micon);
    frame->evaluateJavaScript(marker);
}

void Widget::getCoordinate(const QString &lot, const QString &lat)
{
    qDebug()<<"lot:"<<lot<<" lat:"<<lat;
}

void Widget::slotPopulateJavaScriptWindowObject()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("ReinforcePC", this);
}

void Widget::on_pbnAddMarker_clicked()
{
    QString lot = ui->lineEdit_lot->text();
    QString lat = ui->lineEdit_lat->text();

    addMarker(lot,lat,"images/ship_mark.png");
}
