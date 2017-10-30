#include "svgparsedom.h"

/**Qt include file*/
#include <QFile>
#include <QFileDialog>
#include <QDebug>

#include <QDomDocument>

SVGParsedom::SVGParsedom(QObject *parent)
    : QObject(parent)
{

}

SVGParsedom::~SVGParsedom()
{
}

void SVGParsedom::parse(const QString &strFileName)
{
    if ( strFileName.isEmpty () ){
        qDebug()<<"file name is empty!"<<endl;
        return;
    }
    QFile file(strFileName);
    if ( !file.open (QFile::ReadOnly | QFile::Text)){
        qDebug()<<"open file "<<strFileName <<" error"<<endl;
        return;
    }

    //将XML文件内容读取到dom中
    QDomDocument document;
    if ( !document.setContent (&file)){
        qDebug()<<"parse file failed!";
        file.close ();
        return;
    }
    file.close ();

#if 0
    QDomElement docElem = document.documentElement ();
    QDomNode n = docElem.firstChild ();
    while ( !n.isNull ()){
        QDomElement e = n.toElement ();
        if ( !e.isNull ()){
            qDebug()<<e.tagName ()<<" "<<e.text ()<<endl;
            qDebug()<<"name:"<<e.nodeName ();
        }
        n = n.nextSibling ();
    }
#endif

    QDomNode firstNode = document.firstChild ();
    qDebug()<<firstNode.nodeName ()<< " value:"<<firstNode.nodeValue ();
    //返回根元素
    QDomElement docElem = document.documentElement ();
    //返回根节点的第一个子节点
    QDomNode n = document.firstChild ();
    while ( !n.isNull ())
    {
        QDomElement e = n.toElement ();
        qDebug()<<e.tagName ();
        n = n.nextSibling ();
    }
}
