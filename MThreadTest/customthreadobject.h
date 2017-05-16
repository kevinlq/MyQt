#ifndef CUSTOMTHREADOBJECT_H
#define CUSTOMTHREADOBJECT_H

#include <QObject>

class CustomThreadObject : public QObject
{
    Q_OBJECT
public:
    explicit CustomThreadObject(QObject *parent = 0);
    ~CustomThreadObject();

signals:
    void signalResultReady(const int value);

public slots:

    void slotStart();

    void slotDoWork();
};

#endif // CUSTOMTHREADOBJECT_H
