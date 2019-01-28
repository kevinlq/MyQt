#ifndef TESTRADAR_GLOBAL_H
#define TESTRADAR_GLOBAL_H

#include <qglobal.h>

#if defined(TESTRADAR_LIBRARY)
#  define TESTRADAR_EXPORT Q_DECL_EXPORT
#else
#  define TESTRADAR_EXPORT Q_DECL_IMPORT
#endif

#endif // TESTRADAR_GLOBAL_H
