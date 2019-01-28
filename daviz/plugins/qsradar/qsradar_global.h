#ifndef QSRADAR_GLOBAL_H
#define QSRADAR_GLOBAL_H

#include <qglobal.h>

#if defined(QSRADAR_LIBRARY)
#  define QSRADAR_EXPORT Q_DECL_EXPORT
#else
#  define QSRADAR_EXPORT Q_DECL_IMPORT
#endif

#endif // QSRADAR_GLOBAL_H
