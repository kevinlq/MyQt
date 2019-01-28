#ifndef REPLAY_GLOBAL_H
#define REPLAY_GLOBAL_H

#include <qglobal.h>

#if defined(REPLAY_LIBRARY)
#  define REPLAY_EXPORT Q_DECL_EXPORT
#else
#  define REPLAY_EXPORT Q_DECL_IMPORT
#endif

#endif // REPLAY_GLOBAL_H
