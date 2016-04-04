#ifndef BREAKPAD_GLOBAL_H
#define BREAKPAD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BREAKPAD_LIBRARY)
#  define BREAKPADSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BREAKPADSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BREAKPAD_GLOBAL_H