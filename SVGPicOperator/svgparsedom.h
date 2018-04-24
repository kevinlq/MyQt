#ifndef SVGPARSEDOM_H
#define SVGPARSEDOM_H

#include <QObject>

class SVGParsedom : public QObject
{
    Q_OBJECT
public:
    explicit SVGParsedom(QObject *parent = 0);
    ~SVGParsedom();

    void parse(const QString &strFileName);

Q_SIGNALS:

private Q_SLOTS:

};

#endif // SVGPARSEDOM_H
