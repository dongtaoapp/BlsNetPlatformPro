#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T08:43:40
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = simulatorBase
TEMPLATE = lib

DEFINES += SIMULATORBASE_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

#引入的lib文件，用于引入动态链接库
LIBS+= -lquartz  -lole32  -lGdiplus
LIBS += ..\bin71\common.lib  ..\bin71\elementParse.lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += SimulateBaseGlobal.cpp \
    CPRRealTimeUpdateInterface.cpp \
    CPRShowInterfacesAggregate.cpp \
    ShowCPRActUpdateInterface.cpp \
    ShowCPRStatisticUpdateInterface.cpp \
    CPRStatIrp.cpp \
    EventIrp_ClockTime.cpp \
    EventIrp_SimulateTrigger.cpp \
    FrameFlowIrp.cpp \
    SimulatorOrderIrp.cpp \
    VirEventIrp.cpp \
    ShowEventSignUpdateInterface.cpp \
    IPnPFacility.cpp \
    IUpdateLogDataInterface.cpp \
    OpLogInterface.cpp \
    SyncPnpFacilities.cpp \
    ITypePhysiologyDefaultRange.cpp \
    OpABPBuildInterface.cpp \
    OpECGBuildInterface.cpp \
    OpEtCO2BuildInterface.cpp \
    OpRespBuildInterface.cpp \
    OpSpO2BuildInterface.cpp \
    ShowABPUpdateInterface.cpp \
    ShowECGUpdateInterface.cpp \
    ShowEtCO2UpdateInterface.cpp \
    ShowFrameNameUpdateInterface.cpp \
    ShowFrameTimeUpdateInterface.cpp \
    ShowGeneralNoRangeUpdateInterface.cpp \
    ShowGeneralUpdateInterface.cpp \
    ShowNIBPUpdateInterface.cpp \
    ShowPaceUpdateInterface.cpp \
    ShowPatientTimeUpdateInterface.cpp \
    ShowRespRateUpdateInterface.cpp \
    ShowScenarioRunTimeUpdateInterface.cpp \
    ShowScriptTrainNameUpdateInterface.cpp \
    ShowSpO2UpdateInterface.cpp \
    ShowTempUpdateInterface.cpp \
    IGetPhysioloySimulateData.cpp \
    ICardiogramLeads.cpp \
    ICO2SimulateSign.cpp \
    IDistributeSimulateData.cpp \
    IHeartStartSign.cpp \
    IPaneMoveControlInterface.cpp \
    IPhysiologyStartSign.cpp \
    OpPhysBuildInterfacesAggregate.cpp \
    SymptomsShowInterfacesAggregate.cpp \
    ITransportOrderIrpToSimulator.cpp \
    VirCardiogramParam.cpp \
    WatchBarsShowInterfacesAggregate.cpp \
    WCD.cpp \
    VirCardiogramParaFactory.cpp \
    Sample.cpp \
    CardiogramCoordinate.cpp \
    CardiogramUCD.cpp \
    RealTimeDataIrp.cpp

HEADERS +=\
        simulatorbase_global.h \
    SimulateBaseGlobal.h \
    CPRRealTimeUpdateInterface.h \
    CPRShowInterfacesAggregate.h \
    ShowCPRActUpdateInterface.h \
    ShowCPRStatisticUpdateInterface.h \
    CPRStatIrp.h \
    EventIrp_ClockTime.h \
    EventIrp_SimulateTrigger.h \
    FrameFlowIrp.h \
    SimulatorOrderIrp.h \
    VirEventIrp.h \
    ShowEventSignUpdateInterface.h \
    IPnPFacility.h \
    IUpdateLogDataInterface.h \
    OpLogInterface.h \
    SyncPnpFacilities.h \
    ITypePhysiologyDefaultRange.h \
    OpABPBuildInterface.h \
    OpECGBuildInterface.h \
    OpEtCO2BuildInterface.h \
    OpRespBuildInterface.h \
    OpSpO2BuildInterface.h \
    ShowABPUpdateInterface.h \
    ShowECGUpdateInterface.h \
    ShowEtCO2UpdateInterface.h \
    ShowFrameNameUpdateInterface.h \
    ShowFrameTimeUpdateInterface.h \
    ShowGeneralNoRangeUpdateInterface.h \
    ShowGeneralUpdateInterface.h \
    ShowNIBPUpdateInterface.h \
    ShowPaceUpdateInterface.h \
    ShowPatientTimeUpdateInterface.h \
    ShowRespRateUpdateInterface.h \
    ShowScenarioRunTimeUpdateInterface.h \
    ShowScriptTrainNameUpdateInterface.h \
    ShowSpO2UpdateInterface.h \
    ShowTempUpdateInterface.h \
    IGetPhysioloySimulateData.h \
    ICardiogramLeads.h \
    ICO2SimulateSign.h \
    IDistributeSimulateData.h \
    IHeartStartSign.h \
    IPaneMoveControlInterface.h \
    IPhysiologyStartSign.h \
    OpPhysBuildInterfacesAggregate.h \
    SymptomsShowInterfacesAggregate.h \
    ITransportOrderIrpToSimulator.h \
    VirCardiogramParam.h \
    WatchBarsShowInterfacesAggregate.h \
    WCD.h \
    VirCardiogramParaFactory.h \
    Sample.h \
    CardiogramCoordinate.h \
    CardiogramUCD.h \
    RealTimeDataIrp.h

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

win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_thread-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_thread-vc120-mt-gd-1_56

win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_system-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_system-vc120-mt-gd-1_56

win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_chrono-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_chrono-vc120-mt-gd-1_56

INCLUDEPATH += D:/Boost/boost_1_56_0
DEPENDPATH += D:/Boost/boost_1_56_0
