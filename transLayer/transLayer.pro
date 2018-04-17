#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T14:01:31
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = transLayer
TEMPLATE = lib

#DEFINES += _WINSOCK2API_
DEFINES += WIN32_LEAN_AND_MEAN
DEFINES += TRANSLAYER_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

#引入的lib文件，用于引入动态链接库
#win32:CONFIG(debug, debug|release): LIBS += ws2_32.lib ..\bin71\common.lib ..\bin71\simulatorBase.lib
#else:win32:CONFIG(release, debug|release): LIBS += ws2_32.lib ..\bin\common.lib ..\bin\simulatorBase.lib
LIBS += ws2_32.lib ..\bin71\common.lib ..\bin71\simulatorBase.lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += layerglobal.cpp \
    BufferAndJudgeCPR.cpp \
    FilterDown.cpp \
    FilterUp.cpp \
    FormatTransport.cpp \
    NetSimulateCommunicate.cpp \
    TriggerJudgeGlobal.cpp \
    VirtualCommunicate.cpp

HEADERS += layerglobal.h\
        translayer_global.h \
    BufferAndJudgeCPR.h \
    FilterDown.h \
    FilterUp.h \
    FormatTransport.h \
    NetSimulateCommunicate.h \
    TriggerJudgeGlobal.h \
    VirtualCommunicate.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_thread-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_thread-vc120-mt-gd-1_56

win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_chrono-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_chrono-vc120-mt-gd-1_56

win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_system-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_system-vc120-mt-gd-1_56

INCLUDEPATH += D:/Boost/boost_1_56_0
DEPENDPATH += D:/Boost/boost_1_56_0
