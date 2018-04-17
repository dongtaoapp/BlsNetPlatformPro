#-------------------------------------------------
#
# Project created by QtCreator 2018-04-04T11:23:10
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = simulatorSymptom
TEMPLATE = lib

DEFINES += SIMULATORSYMPTOM_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

#引入的lib文件，用于引入动态链接库
LIBS+= -lquartz  -lole32  -lGdiplus
LIBS += ..\bin71\common.lib  ..\bin71\elementParse.lib ..\bin71\simulatorBase.lib

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

SOURCES += symptomvirtual.cpp \
    IModifiedSymptomsOp.cpp \
    ISetSimulateSymptoms.cpp \
    PnPFacilityGlobal.cpp \
    SimulateSymptomsCollect.cpp \
    Symptom_ABP.cpp \
    Symptom_CellColumn.cpp \
    Symptom_ContactPatient.cpp \
    Symptom_Defibri.cpp \
    Symptom_Ecg.cpp \
    Symptom_Electrode.cpp \
    Symptom_etCO2.cpp \
    Symptom_FrameTime.cpp \
    Symptom_Pace.cpp \
    Symptom_Pupil.cpp \
    Symptom_Resp.cpp \
    Symptom_SpO2.cpp \
    Symptom_Temperature.cpp \
    SymptomUnmonitorVirtual.cpp \
    VirSimulateSymptomsCollect.cpp \
    XAction_ABP.cpp \
    XAction_CellColumn.cpp \
    XAction_ContactPatient.cpp \
    XAction_CPR.cpp \
    XAction_Defibri.cpp \
    XAction_ECG.cpp \
    XAction_Electrode.cpp \
    XAction_etCO2.cpp \
    XAction_FrameTime.cpp \
    XAction_Osat.cpp \
    XAction_Pace.cpp \
    XAction_Pupil.cpp \
    XAction_Resp.cpp \
    XAction_ScriptRunTime.cpp \
    XAction_Temperature.cpp \
    XActionVirtual.cpp \
    XActionVitalSignVir.cpp \
    XVirtualComponent.cpp

HEADERS += symptomvirtual.h\
        simulatorsymptom_global.h \
    IModifiedSymptomsOp.h \
    ISetSimulateSymptoms.h \
    PnPFacilityGlobal.h \
    SimulateSymptomsCollect.h \
    Symptom_ABP.h \
    Symptom_CellColumn.h \
    Symptom_ContactPatient.h \
    Symptom_Defibri.h \
    Symptom_Ecg.h \
    Symptom_Electrode.h \
    Symptom_etCO2.h \
    Symptom_FrameTime.h \
    Symptom_Pace.h \
    Symptom_Pupil.h \
    Symptom_Resp.h \
    Symptom_SpO2.h \
    Symptom_Temperature.h \
    SymptomUnmonitorVirtual.h \
    VirSimulateSymptomsCollect.h \
    XAction_ABP.h \
    XAction_CellColumn.h \
    XAction_ContactPatient.h \
    XAction_CPR.h \
    XAction_Defibri.h \
    XAction_ECG.h \
    XAction_Electrode.h \
    XAction_etCO2.h \
    XAction_FrameTime.h \
    XAction_Osat.h \
    XAction_Pace.h \
    XAction_Pupil.h \
    XAction_Resp.h \
    XAction_ScriptRunTime.h \
    XAction_Temperature.h \
    XActionVirtual.h \
    XActionVitalSignVir.h \
    XVirtualComponent.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixml
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixmld

INCLUDEPATH += D:/Boost/pugixml-1.8/src
DEPENDPATH += D:/Boost/pugixml-1.8/src

win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_thread-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_thread-vc120-mt-gd-1_56

INCLUDEPATH += D:/Boost/boost_1_56_0
DEPENDPATH += D:/Boost/boost_1_56_0
