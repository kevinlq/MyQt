#ifndef READFIELDOBJ_H
#define READFIELDOBJ_H

#include <QObject>

class ReadFieldObj : public QObject
{
    Q_OBJECT
public:
    explicit ReadFieldObj(const QString &table = "",
                          const QString &field = "",
                          QObject *parent = 0);
    ~ReadFieldObj();

    void setTablInfo(const QString &table,
                     const QString &field);

private:
    void init();

Q_SIGNALS:
    void signalSendDbField(const QString &field);

private Q_SLOTS:
    void slotStartReadDbField();

private:
    QString m_table;
    QString m_field;
};

#endif // READFIELDOBJ_H
