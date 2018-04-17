#-------------------------------------------------
#
# Project created by QtCreator 2018-04-03T13:23:34
#
#-------------------------------------------------

QT       -= gui

DESTDIR += ../bin71
TARGET = adultParams
TEMPLATE = lib

DEFINES += ADULTPARAMS_LIBRARY
DEFINES += BOOST_USE_LIB
INCLUDEPATH += D:/Boost/boost_1_56_0

#引入的lib文件，用于引入动态链接库
LIBS+= -lquartz  -lole32  -lGdiplus
LIBS += ..\bin71\common.lib  ..\bin71\simulatorBase.lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += adultrespparam.cpp \
    AdultApneaRespParam.cpp \
    AdultApneusticRespParam.cpp \
    AdultBiotsRespParam.cpp \
    AdultCardiogramParamFactory.cpp \
    AdultSignRespParam.cpp \
    Cardiogram1degree_AVB.cpp \
    Cardiogram1degree_AVBParam_I12.cpp \
    Cardiogram2degree_AVBI.cpp \
    Cardiogram2degree_AVBII.cpp \
    Cardiogram2degree_AVBIIParam_I12.cpp \
    Cardiogram2degree_AVBIParam_I12.cpp \
    Cardiogram3degree_AVB.cpp \
    Cardiogram3degree_AVBParam_I12.cpp \
    CardiogramA_fib.cpp \
    CardiogramA_fibParam_I12.cpp \
    CardiogramA_flutt.cpp \
    CardiogramA_fluttParam_I12.cpp \
    CardiogramAgonale.cpp \
    CardiogramAgonaleParam_I12.cpp \
    CardiogramAsystole.cpp \
    CardiogramAsystoleParam_I12.cpp \
    CardiogramIdiov.cpp \
    CardiogramIdiovParam_I12.cpp \
    CardiogramJunct.cpp \
    CardiogramJunctParam_I12.cpp \
    CardiogramOthers.cpp \
    CardiogramOthersParam_I12.cpp \
    CardiogramPace.cpp \
    CardiogramPaceParam_I12.cpp \
    CardiogramS_tach.cpp \
    CardiogramS_tachParam_I12.cpp \
    CardiogramSinus.cpp \
    CardiogramSinusParam_I12.cpp \
    CardiogramTorsade_DP.cpp \
    CardiogramTorsade_DPParam_I12.cpp \
    CardiogramV_flutt.cpp \
    CardiogramV_fluttParam_I12.cpp \
    CardiogramV_tach.cpp \
    CardiogramV_tachParam_I12.cpp \
    CardiogramVFibr.cpp \
    CardiogramVFibrParam_I12.cpp

HEADERS += adultrespparam.h\
        adultparams_global.h \
    AdultApneaRespParam.h \
    AdultApneusticRespParam.h \
    AdultBiotsRespParam.h \
    AdultCardiogramParamFactory.h \
    AdultSignRespParam.h \
    Cardiogram1degree_AVB.h \
    Cardiogram1degree_AVBParam_I12.h \
    Cardiogram2degree_AVBI.h \
    Cardiogram2degree_AVBII.h \
    Cardiogram2degree_AVBIIParam_I12.h \
    Cardiogram2degree_AVBIParam_I12.h \
    Cardiogram3degree_AVB.h \
    Cardiogram3degree_AVBParam_I12.h \
    CardiogramA_fib.h \
    CardiogramA_fibParam_I12.h \
    CardiogramA_flutt.h \
    CardiogramA_fluttParam_I12.h \
    CardiogramAgonale.h \
    CardiogramAgonaleParam_I12.h \
    CardiogramAsystole.h \
    CardiogramAsystoleParam_I12.h \
    CardiogramIdiov.h \
    CardiogramIdiovParam_I12.h \
    CardiogramJunct.h \
    CardiogramJunctParam_I12.h \
    CardiogramOthers.h \
    CardiogramOthersParam_I12.h \
    CardiogramPace.h \
    CardiogramPaceParam_I12.h \
    CardiogramS_tach.h \
    CardiogramS_tachParam_I12.h \
    CardiogramSinus.h \
    CardiogramSinusParam_I12.h \
    CardiogramTorsade_DP.h \
    CardiogramTorsade_DPParam_I12.h \
    CardiogramV_flutt.h \
    CardiogramV_fluttParam_I12.h \
    CardiogramV_tach.h \
    CardiogramV_tachParam_I12.h \
    CardiogramVFibr.h \
    CardiogramVFibrParam_I12.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


win32:CONFIG(release, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_locale-vc120-mt-1_56
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Boost/boost_1_56_0/vc12_x86/lib/ -llibboost_locale-vc120-mt-gd-1_56

INCLUDEPATH += D:/Boost/boost_1_56_0
DEPENDPATH += D:/Boost/boost_1_56_0
