#include "parsedom.h"

#include <QDomDocument>
#include <QFile>

#include <QDebug>

ParseDom::ParseDom(QObject *parent)
    : QObject(parent)
{
}

ParseDom::~ParseDom()
{
}

void ParseDom::parse(const QString &fileName)
{
    if ( fileName.isEmpty ()){
        qDebug()<<"xml file is empty"<<endl;
        return;
    }

    QFile file(fileName);
    if ( !file.open (QIODevice::ReadOnly)){
        qDebug()<<"xml file open failed!"<<endl;
        return;
    }
    QDomDocument doc("person");
    if ( !doc.setContent (&file)){
        qDebug()<<"parse file failed";
        file.close ();
        return;
    }

    //打印出最外层元素的所有直接元素名称
    QDomElement docElem = doc.documentElement ();

    QDomNode n = docElem.firstChild ();
    while (!n.isNull ())
    {
        //尝试将节点转换为元素
        QDomElement e = n.toElement ();
        if ( !e.isNull ())
        {
            qDebug()<<e.tagName ()<<" "<<e.text ()<<endl;
        }
        n = n.nextSibling ();
    }
}

void ParseDom::parse2(const QString &fileName)
{
    if ( fileName.isEmpty () )
        return;
    QFile file( fileName );
    if ( !file.open (QFile::ReadOnly | QFile::Text)){
        qDebug()<<"open file "<<fileName << " error!"<<endl;
        return;
    }

    QDomDocument document;
    QString error;
    int row = 0,column = 0;
    if ( !document.setContent (&file,false,&error,&row,&column))
    {
        qDebug()<< QString("parse file failed at line  row: %1 column:%2").arg (row).arg (column);
        file.close ();
        return;
    }

    if ( document.isNull ()){
        qDebug()<<"documentis null!"<<endl;
        return;
    }

    QDomElement root = document.documentElement ();
    QString rootTagName = root.tagName ();
    if ( root.hasAttribute ("name"))
    {
        QString name = root.attributeNode ("name").value ();
        qDebug()<<"name:"<<name;
    }

    //获取id = 1的节点
    QDomElement person = root.firstChildElement ();
    if ( person.isNull ())
        return;

    //id 为1
    QString id = person.attributeNode ("id").value ();

    //获取子节点，数目为2
    QDomNodeList list = root.childNodes ();
    int count = list.count ();
    for ( int i = 0; i < count; i++)
    {
        QDomNode domNode = list.item (i);
        QDomElement element = domNode.toElement ();

        //获取id值
        QString id1 = element.attributeNode ("id").value ();
        QString id2 = element.attribute ("id");

        qDebug()<<"id1:"<<id1;
        qDebug()<<"id2:"<<id2;

        //获取子节点，数目为4
        QDomNodeList childList = element.childNodes ();
        int childCount = childList.count ();
        for ( int j = 0; j < childCount; j++)
        {
            QDomNode childDomNode = childList.item (j);
            QDomElement childElement = childDomNode.toElement ();
            QString childTagName = childElement.tagName ();
            QString childTagValue = childElement.text ();

            qDebug()<<"tagName:"<<childTagName;
            qDebug()<<"tagValue:"<<childTagValue;
        }
    }

    //按照name,age,email,website顺序进行获取
    //    QDomElement element = person.firstChildElement ();
    //    while ( !element.isNull ())
    //    {
    //        QString tagName = element.tagName ();
    //        QString tagValue = element.text ();

    //        qDebug()<<"tagName:"<<tagName;
    //        qDebug()<<"tagValue:"<<tagValue;

    //        element = element.nextSiblingElement ();
    //    }
}
