#include "widget.h"
#include "ui_widget.h"

#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QMatrix>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_strPath = QApplication::applicationDirPath ();

    qDebug()<<m_strPath;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    unsigned char *grayData;
    QImage img;
    img.load (m_strPath+"/2.jpg");

    QPixmap pixmap(QPixmap::fromImage (img));

    ui->label->setPixmap (pixmap);

    unsigned char *data = img.bits ();

    int w = img.width ();
    int h = img.height ();

    int bytePerLine = (w * 24 + 31) / 8;
    //存储处理后的数据
    grayData = new unsigned char [bytePerLine * h];
    unsigned char r,g,b;
    for ( int i = 0; i < h; i++ )
    {
        for ( int j = 0; j < w; j++ )
        {
            r =  *(data + 2);
            g = *(data + 1);
            b = *data;

            grayData[i * bytePerLine + j * 3] = (r * 30 + g*59 +b*11)/100;
            grayData[i*bytePerLine+j*3+1]=(r*30+g*59+b*11)/100;
            grayData[i*bytePerLine+j*3+2]=(r*30+g*59+b*11)/100;

            data+=4;

            //ui->textEdit->append (QString("%1 %2 %3").arg (r).arg (g).arg (b));
        }
    }

    QImage grayImage(grayData,w,h,bytePerLine,QImage::Format_RGB888);

    QPixmap pixmap2(QPixmap::fromImage (grayImage));

    ui->label_2->setPixmap (pixmap2);
}
