#include "widget.h"
#include "ui_widget.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

#define MY_ITEM_NUM    10
#define ITEM_HEIGHT     50

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_vtrItem.clear ();

    m_nPageSize = -1;
    m_nRecordCount = MY_ITEM_NUM;
    m_nPageCount = -1;

    //计算listwidget的高度，然后可以计算出没页可以显示的item数量
    int nViewHight = ui->listWidget->height ();
    m_nPageSize = nViewHight /ITEM_HEIGHT;

    qDebug()<<"height:"<<nViewHight<<" size:"<<m_nPageSize;

#if 1
    //创建item
    for (int i = 0; i < m_nRecordCount; i++)
    {
        MyItem *pItem = new MyItem;
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        int nRow = ui->listWidget->count ();
        ui->listWidget->insertItem (nRow,item);
        ui->listWidget->setItemWidget (item,pItem);
        item->setSizeHint (QSize(0,ITEM_HEIGHT));

        m_vtrItem.push_back (pItem);
    }
#endif
}

Widget::~Widget()
{
    delete ui;

    qDeleteAll(m_vtrItem);
    m_vtrItem.clear ();
}

void Widget::insertItem(int nTotalNum)
{
    if ( nTotalNum >= m_nPageSize )
    {
        //
    }
}

void Widget::on_pbnPre_clicked()
{
    //
}

void Widget::on_pbnNext_clicked()
{
    //
}

MyItem::MyItem()
{
    m_nPeriod = -1;

    m_pLabelStr = new QLabel(this);
    m_pLabelStr->setText ("this is sample");
    m_pPbnChange = new QPushButton(this);
    m_pPbnChange->setText ("change");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget (m_pLabelStr);
    layout->addWidget (m_pPbnChange);

    setLayout (layout);
}

MyItem::~MyItem()
{
}
