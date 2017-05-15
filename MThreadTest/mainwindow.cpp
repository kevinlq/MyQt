#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "customthreadobject.h"

#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug()<<"main thread id:"<<QThread::currentThreadId();

}

MainWindow::~MainWindow()
{
    delete ui;
}
