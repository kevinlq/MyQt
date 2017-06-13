#ifndef LDBHANDLE_H
#define LDBHANDLE_H

#include <QStringList>

class LDbHandle
{
public:
    LDbHandle();
    ~LDbHandle();

    static QStringList getTableNames();

    static QStringList getTableFieldNames(const QString &tableName);
};

#endif // LDBHANDLE_H
