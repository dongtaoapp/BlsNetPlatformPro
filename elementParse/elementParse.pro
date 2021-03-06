#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T17:17:51
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = elementParse
TEMPLATE = lib

DEFINES += ELEMENTPARSE_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += saction_abp.cpp \
    SAction_CellColumn.cpp \
    SAction_ContactPatient.cpp \
    SAction_Defibrillate.cpp \
    SAction_ECG.cpp \
    SAction_Electrode.cpp \
    SAction_etCO2.cpp \
    SAction_FrameTime.cpp \
    SAction_Osat.cpp \
    SAction_Pace.cpp \
    SAction_PatientTime.cpp \
    SAction_Pupil.cpp \
    SAction_Resp.cpp \
    SAction_SceneTime.cpp \
    SAction_Temperature.cpp \
    SEvent_AED.cpp \
    SEvent_CPR.cpp \
    SEvent_Defibr.cpp \
    SEvent_Intubate.cpp \
    SEvent_Pace.cpp \
    SEvent_Pulse.cpp \
    SEvent_Thump.cpp \
    SEvent_Time.cpp

HEADERS += saction_abp.h\
        elementparse_global.h \
    SAction_CellColumn.h \
    SAction_ContactPatient.h \
    SAction_Defibrillate.h \
    SAction_ECG.h \
    SAction_Electrode.h \
    SAction_etCO2.h \
    SAction_FrameTime.h \
    SAction_Osat.h \
    SAction_Pace.h \
    SAction_PatientTime.h \
    SAction_Pupil.h \
    SAction_Resp.h \
    SAction_SceneTime.h \
    SAction_Temperature.h \
    SEvent_AED.h \
    SEvent_CPR.h \
    SEvent_Defibr.h \
    SEvent_Intubate.h \
    SEvent_Pace.h \
    SEvent_Pulse.h \
    SEvent_Thump.h \
    SEvent_Time.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixml
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/pugixml-1.8/vc14_x86/lib/ -lpugixmld

INCLUDEPATH += D:/Boost/pugixml-1.8/src
DEPENDPATH += D:/Boost/pugixml-1.8/src
