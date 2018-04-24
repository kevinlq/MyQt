#ifndef SYSTEMPATHINFO_H
#define SYSTEMPATHINFO_H

#include <QObject>

class SystemPathInfo : public QObject
{
    Q_OBJECT
public:
    explicit SystemPathInfo(QObject *parent = nullptr);
    ~SystemPathInfo();

Q_SIGNALS:
    void pathChanged(const QString &strPath);

public Q_SLOTS:
    void slotOnSend();

};

#endif // SYSTEMPATHINFO_H
