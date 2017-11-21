#include "widget.h"
#include "ui_widget.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

#define MY_ITEM_SIZE    100

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_vtrItem.clear ();

    m_nPageSize = -1;
    m_nRecordCount = MY_ITEM_SIZE;
    m_nPageCount = -1;

    //创建item
    for (int i = 0; i < m_nRecordCount; i++)
    {
        MyItem *pItem = new MyItem;
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        int nRow = ui->listWidget->count ();
        ui->listWidget->insertItem (nRow,item);
        ui->listWidget->setItemWidget (item,pItem);
        item->setSizeHint (QSize(0,50));

        m_vtrItem.push_back (pItem);
    }
}

Widget::~Widget()
{
    delete ui;

    if ( !m_vtrItem.isEmpty ())
    {
        for ( int i = 0; i < m_vtrItem.size (); i++)
        {
            if ( m_vtrItem[i] != NULL)
            {
                delete m_vtrItem[i];
                m_vtrItem[i] = NULL;
            }
        }
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
