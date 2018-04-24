#ifndef PARSEDOM_H
#define PARSEDOM_H

#include <QObject>

class ParseDom : public QObject
{
    Q_OBJECT
public:
    explicit ParseDom(QObject *parent = 0);
    ~ParseDom();

    void parse(const QString &fileName);

    void parse2(const QString &fileName);

Q_SIGNALS:

public Q_SLOTS:

};

#endif // PARSEDOM_H
