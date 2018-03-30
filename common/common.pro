#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T09:12:48
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = common
TEMPLATE = lib

DEFINES += COMMON_LIBRARY
LIBS += ws2_32.lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += BOOST_USE_LIB

#win32:LIBS +=  _L($$(WINDDK_LIB_WIN7_32B_DIR)) -lws2_32
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CommonGlobal.cpp \
    DecodeUtil.cpp \
    VirBuffer.cpp \
    LineBuffer.cpp \
    LoopBuffer.cpp \
    EncodeConv.cpp \
    RefLexical_cast.cpp \
    RefLexical_laug_cast.cpp \
    VirTcpTransferOpGather.cpp \
    IBedirecteLinksVir.cpp \
    NetTransferCommonGlobal.cpp \
    PatientRuleInterfaceGlobal.cpp \
    ECGParams.cpp \
    AdultPatient.cpp \
    AdultPatient_Singleton.cpp \
    PatientTypeFactory.cpp \
    PatientTypeRule.cpp \
    IUpdateShowVir.cpp \
    EventHandleClockIrpOp.cpp \
    EventHandleCPRStatIrpOp.cpp \
    EventHandleCustomIrpOp.cpp \
    EventHandleFrameFlowIrpOp.cpp \
    EventHandleSimulateTriggerIrpOp.cpp \
    OpInterfaceVir.cpp \
    ParseCPRData_Singleton.cpp \
    VirHandleIrpOp.cpp \
    VirtualIrp.cpp \
    criticalmutex.cpp \
    NetTransferVir.cpp \
    RealTimeDataHandleIrpOp.cpp

HEADERS +=\
        common_global.h \
    CommonGlobal.h \
    DecodeUtil.h \
    VirBuffer.h \
    LineBuffer.h \
    LoopBuffer.h \
    EncodeConv.h \
    RefLexical_cast.h \
    RefLexical_laug_cast.h \
    VirTcpTransferOpGather.h \
    IBedirecteLinksVir.h \
    NetTransferCommonGlobal.h \
    PatientRuleInterfaceGlobal.h \
    ECGParams.h \
    AdultPatient.h \
    AdultPatient_Singleton.h \
    PatientTypeFactory.h \
    PatientTypeRule.h \
    IUpdateShowVir.h \
    EventHandleClockIrpOp.h \
    EventHandleCPRStatIrpOp.h \
    EventHandleCustomIrpOp.h \
    EventHandleFrameFlowIrpOp.h \
    EventHandleSimulateTriggerIrpOp.h \
    OpInterfaceVir.h \
    ParseCPRData_Singleton.h \
    VirHandleIrpOp.h \
    VirtualIrp.h \
    criticalmutex.h \
    NetTransferVir.h \
    RealTimeDataHandleIrpOp.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixml
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixmld

INCLUDEPATH += D:/Boost/pugixml-1.8/src
DEPENDPATH += D:/Boost/pugixml-1.8/src


win32:LIBS += -LD:/Boost/iconv-1.9.2.win32/lib/ -liconv

INCLUDEPATH += D:/Boost/iconv-1.9.2.win32/include
DEPENDPATH += D:/Boost/iconv-1.9.2.win32/include


win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_locale-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_locale-vc120-mt-gd-1_56

INCLUDEPATH += D:/Boost/boost_1_56_0
DEPENDPATH += D:/Boost/boost_1_56_0
