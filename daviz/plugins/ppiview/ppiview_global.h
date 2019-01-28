#ifndef PPIVIEW_GLOBAL_H
#define PPIVIEW_GLOBAL_H

#include <qglobal.h>

#if defined(PPIVIEW_LIBRARY)
#  define PPIVIEW_EXPORT Q_DECL_EXPORT
#else
#  define PPIVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // PPIVIEW_GLOBAL_H
