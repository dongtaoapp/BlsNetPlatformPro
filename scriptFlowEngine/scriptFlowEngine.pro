#-------------------------------------------------
#
# Project created by QtCreator 2018-04-04T13:45:15
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = scriptFlowEngine
TEMPLATE = lib

DEFINES += SCRIPTFLOWENGINE_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

LIBS += ..\bin71\common.lib  ..\bin71\elementParse.lib ..\bin71\simulatorBase.lib ..\bin71\simulatorEmulateBuild.lib ..\bin71\transLayer.lib ..\bin71\cprModuls.lib ..\bin71\physiologyWatchBar.lib ..\bin71\simulatorSymptom.lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += WIN32_LEAN_AND_MEAN

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += xvirtuallink.cpp \
    BLSConfigue.cpp \
    BlsLogs.cpp \
    BlsMainFlowOwn.cpp \
    BlsMainFlowVirtual.cpp \
    BlsMainFlowWatch.cpp \
    BlsSimulateCase.cpp \
    EventLogUpdate_Singleton.cpp \
    IAclsFlowStrategy.cpp \
    IGetPhysiologyActionObj.cpp \
    IHandleIrpsCollect.cpp \
    ISceneActRunOp.cpp \
    NormalAclsFlowStrategy.cpp \
    ParseShapeFactory.cpp \
    SceneActsCollect.cpp \
    XCombineEventsFrame.cpp \
    XEvent_AED.cpp \
    XEvent_CPR.cpp \
    XEvent_Defibri.cpp \
    XEvent_Pulse.cpp \
    XEvent_Thump.cpp \
    XEvent_Time.cpp \
    XEventVirtual.cpp \
    XLineLink.cpp \
    XLineLinkEventObj.cpp \
    XLineLinkScenarioObj.cpp \
    XRunFramework.cpp \
    XScenario.cpp \
    XSceneActFrame.cpp \
    XSelEventsFrame.cpp \
    XSingleEventFrame.cpp \
    XVirtualEventFrame.cpp

HEADERS += xvirtuallink.h\
        scriptflowengine_global.h \
    BLSConfigue.h \
    BlsLogs.h \
    BlsMainFlowOwn.h \
    BlsMainFlowVirtual.h \
    BlsMainFlowWatch.h \
    BlsSimulateCase.h \
    EventLogUpdate_Singleton.h \
    IAclsFlowStrategy.h \
    IGetPhysiologyActionObj.h \
    IHandleIrpsCollect.h \
    ISceneActRunOp.h \
    NormalAclsFlowStrategy.h \
    ParseShapeFactory.h \
    SceneActsCollect.h \
    XCombineEventsFrame.h \
    XEvent_AED.h \
    XEvent_CPR.h \
    XEvent_Defibri.h \
    XEvent_Pulse.h \
    XEvent_Thump.h \
    XEvent_Time.h \
    XEventVirtual.h \
    XLineLink.h \
    XLineLinkEventObj.h \
    XLineLinkScenarioObj.h \
    XRunFramework.h \
    XScenario.h \
    XSceneActFrame.h \
    XSelEventsFrame.h \
    XSingleEventFrame.h \
    XVirtualEventFrame.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixml
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixmld

INCLUDEPATH += D:/Boost/pugixml-1.8/src
DEPENDPATH += D:/Boost/pugixml-1.8/src


win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_locale-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_locale-vc120-mt-gd-1_56

INCLUDEPATH += D:/Boost/boost_1_56_0
DEPENDPATH += D:/Boost/boost_1_56_0
