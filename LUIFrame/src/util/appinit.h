#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>

class readFromTcpServer;

class AppInit : public QObject
{
    Q_OBJECT
public:
    explicit AppInit(QObject *parent = 0);
    ~AppInit();

    void init();

Q_SIGNALS:

private Q_SLOTS:

private:
    readFromTcpServer   *m_pReadFromTcp;
};

#endif // APPINIT_H
