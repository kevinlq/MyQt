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

    QDomDocument document("fill");
    if ( !document.setContent (&file)){
        qDebug()<<"parse file failed!";
        file.close ();
        return;
    }

    QDomElement docElem = document.documentElement ();
    QDomNode n = docElem.firstChild ();
    while ( !n.isNull ()){
        QDomElement e = n.toElement ();
        if ( !e.isNull ()){
            qDebug()<<e.tagName ()<<" "<<e.text ()<<endl;
            if (e.nodeName () == "svg"){
                qDebug()<<"node name:"<<e.nodeName ();
            }
        }
        n = n.nextSibling ();
    }

}
