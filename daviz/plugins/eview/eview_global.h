#ifndef EVIEW_GLOBAL_H
#define EVIEW_GLOBAL_H

#include <qglobal.h>

#if defined(EVIEW_LIBRARY)
#  define EVIEW_EXPORT Q_DECL_EXPORT
#else
#  define EVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // EVIEW_GLOBAL_H
