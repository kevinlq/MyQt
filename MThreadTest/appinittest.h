#ifndef APPINITTEST_H
#define APPINITTEST_H

#include <QObject>

class CustomThreadObject;
class QThread;
class QTimer;

class AppInitTest : public QObject
{
    Q_OBJECT
public:
    explicit AppInitTest(QObject *parent = 0);
    ~AppInitTest();

    void init();

signals:

public slots:

private:
    CustomThreadObject  *m_pCusThreadObj;
    QThread             *m_pThread;
    QTimer              *m_pTimer;
};

#endif // APPINITTEST_H
