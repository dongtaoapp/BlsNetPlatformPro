#ifndef COMMON_GLOBAL_H
#define COMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMON_LIBRARY)
#  define AFX_EXT_CLASS Q_DECL_EXPORT
#else
#  define AFX_EXT_CLASS Q_DECL_IMPORT
#endif


typedef unsigned char byte;


#endif // COMMON_GLOBAL_H
