#ifndef ELEMENTPARSE_GLOBAL_H
#define ELEMENTPARSE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ELEMENTPARSE_LIBRARY)
#  define AFX_EXT_CLASS Q_DECL_EXPORT
#else
#  define AFX_EXT_CLASS Q_DECL_IMPORT
#endif

#endif // ELEMENTPARSE_GLOBAL_H
