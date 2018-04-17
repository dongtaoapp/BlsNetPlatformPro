#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T18:12:26
#
#-------------------------------------------------

QT       += gui widgets core

DESTDIR += ../bin71
TARGET = cprModuls
TEMPLATE = lib

DEFINES += CPRMODULS_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

#引入的lib文件，用于引入动态链接库
LIBS += ..\bin71\common.lib  ..\bin71\elementParse.lib ..\bin71\simulatorBase.lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += cprcommonglobal.cpp \
    3DVirRealtyNetProxy.cpp \
    Collates.cpp \
    CPRConfigue.cpp \
    CPRMessageCollect.cpp \
    CPRPhaseStatistic.cpp \
    CPRSimulateJudgeOp.cpp \
    CPRStatisticImplement.cpp \
    INetAgencyClient.cpp \
    NetAgenciesSendMgr.cpp \
    cprrealtimeshowwndx2.cpp \
    cprrealtimecavue.cpp \
    ccprrealtimesamplescanvas.cpp \
    cprsamplebufferstate.cpp \
    idistributecprrealtimedata.cpp \
    cprrealtimeshowwndx1.cpp \
    cprrealtimepresurerateshowwnd.cpp \
    qrunningtimewnd.cpp \
    cprrealtimeshowwndx6.cpp

HEADERS += cprcommonglobal.h\
        cprmoduls_global.h \
    3DVirRealtyNetProxy.h \
    Collates.h \
    CPRConfigue.h \
    CPRMessageCollect.h \
    CPRPhaseStatistic.h \
    CPRSimulateJudgeOp.h \
    CPRStatisticImplement.h \
    INetAgencyClient.h \
    NetAgenciesSendMgr.h \
    cprrealtimeshowwndx2.h \
    cprrealtimecavue.h \
    ccprrealtimesamplescanvas.h \
    cprsamplebufferstate.h \
    idistributecprrealtimedata.h \
    cprrealtimeshowwndx1.h \
    cprrealtimepresurerateshowwnd.h \
    qrunningtimewnd.h \
    cprrealtimeshowwndx6.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32: LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_date_time-vc120-mt-gd-1_56

FORMS += \
    cprrealtimeshowwndx2.ui \
    cprrealtimecavue.ui \
    cprrealtimeshowwndx1.ui \
    cprrealtimepresurerateshowwnd.ui \
    cprrealtimeshowwndx6.ui

RESOURCES += \
    res.qrc
