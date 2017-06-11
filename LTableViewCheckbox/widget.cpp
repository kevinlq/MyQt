#include "widget.h"
#include "ui_widget.h"

#include "tablemodel.h"
#include "checkboxdelegate.h"

#include <QTime>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pMode = new TableModel(this);
    m_pDelegate = new CheckBoxDelegate(this);

    ui->tableView->setSelectionBehavior (QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader ()->setStretchLastSection (true);
    ui->tableView->horizontalHeader ()->setHighlightSections (false);
    ui->tableView->verticalHeader ()->setVisible (false);
    ui->tableView->setShowGrid (true);
    ui->tableView->setFrameShape (QFrame::NoFrame);
    ui->tableView->setSelectionMode (QAbstractItemView::SingleSelection);

    ui->tableView->setModel (m_pMode);
    ui->tableView->setItemDelegate (m_pDelegate);

    QTime now;
    now.start ();

    bool status = false;
    //加载数据
    for (int i = 0;i < 10;i++)
    {
        FileRecord record;
        record.bChecked = status;
        record.strFilePath = QString("E:/Qt/file/pic/image_%1.png").arg(i);
        record.strFileSize = QString("%1KB").arg (i*10);
        record.strSpeed = QString("%1KB/s").arg (i);
        m_recordList.append (record);
    }

    m_pMode->updateData (m_recordList);

    updateCheckStatus();

    //根据内容自动调节列宽
    ui->tableView->resizeColumnsToContents ();
    //ui->tableView->resizeRowsToContents ();

    qDebug ()<<now.elapsed ()/1000.0<<" s";

    connect (m_pDelegate,SIGNAL(signalCheckChange(bool,int)),
             this,SLOT(slotDateChange(bool,int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateCheckStatus()
{
    foreach (fileRecord cord, m_recordList) {
        if (!cord.bChecked){
            ui->checkBox->setChecked (false);
            return;
        }
        ui->checkBox->setChecked (true);
    }
}

bool Widget::deleteRowItem()
{
#if 0
    //    foreach (int row, m_rowList) {
    //        m_recordList.removeAt (row);
    //    }
    if (m_rowList.count () == m_recordList.count ()){
        m_recordList.clear ();
        m_rowList.clear ();
        ui->checkBox->setChecked (false);
        return true;
    }

    for (int i = m_rowList.takeFirst ();i < m_rowList.count ();i++)
    {
        m_recordList.removeAt (i);
    }

    m_rowList.clear ();

    return true;
#endif

    //    int count = m_recordList.count ();
    //    for (int i = 0;i < count;i++)
    //    {
    //        if (m_recordList[i].bChecked){
    //            m_recordList.removeAt (i);
    //            qDebug ()<<i;
    //        }
    //    }


    if (m_recordList.isEmpty ())
        return false;

    QMutableListIterator<fileRecord> iter(m_recordList);
    while(iter.hasNext ())
    {
        if (iter.next ().bChecked){
            iter.remove ();
        }
    }

    return  true;
}

void Widget::slotDateChange(const bool flag, const int row)
{
    QString result;
    if (flag){
        result = "true";
    }
    else{
        result = "false";
    }

    m_recordList[row].bChecked = flag;

    updateCheckStatus();

    ui->lineEdit->setText (QString("row:%1 check status:%2")
                           .arg (row).arg (result));
}



void Widget::on_pbn_add_clicked()
{
    ui->checkBox->setEnabled (true);
    fileRecord record;
    record.bChecked = false;
    record.strFilePath = QString("E:/Qt/file/pic/image_%1.png").arg (qrand ()%100);
    record.strFileSize = QString("%1KB").arg (qrand ()%20);
    record.strSpeed = QString("%1KB").arg (qrand ()%40);

    m_recordList.append (record);
    m_pMode->updateData (m_recordList);
}

void Widget::on_pbnDelete_clicked()
{
    if (!deleteRowItem ()){
        qDebug ()<<"delete error!";
        return;
    }

    if (m_recordList.isEmpty ()){
        ui->checkBox->setChecked (false);
        ui->checkBox->setEnabled (false);
    }

    m_pMode->updateData (m_recordList);
}

void Widget::on_checkBox_clicked(bool checked)
{
    if (m_recordList.isEmpty ()){
        ui->checkBox->setEnabled (false);
        return;
    }
    for (int i = 0; i < m_recordList.count ();i++)
    {
        m_recordList[i].bChecked = checked;

        //updateRowList (i,checked);
    }
    m_pMode->updateData (m_recordList);
}
