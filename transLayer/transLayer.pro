#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T14:01:31
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = transLayer
TEMPLATE = lib

DEFINES += TRANSLAYER_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

#引入的lib文件，用于引入动态链接库
LIBS += ws2_32.lib ..\bin71\common.lib

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
