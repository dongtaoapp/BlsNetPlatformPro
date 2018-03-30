DEPENDPATH  += $$PWD
INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/cprworkwnd.ui

HEADERS += \
    $$PWD/cprworkdefin.h \
    $$PWD/cprworkwnd.h

SOURCES += \
    $$PWD/cprworkwnd.cpp

include($$PWD/Popout/Popout.pri)
include($$PWD/StackWidget/CPRStackWnd.pri)

