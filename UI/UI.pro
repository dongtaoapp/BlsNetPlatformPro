#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T13:20:44
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlsNetPlatformPro
TEMPLATE = app

include($$PWD/CPRWorkWnd/CPRWork.pri)

include($$PWD/LoginWnd/LoginWnd.pri)

include($$PWD/ChartWnd/ChartWnd.pri)

include($$PWD/CSWnd/CSWnd.pri)


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



RESOURCES += \
    resources.qrc

FORMS += \
    mainwnd.ui

HEADERS += \
    mainwnd.h

SOURCES += \
    main.cpp \
    mainwnd.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin71/ -lsimulatorBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin71/ -lsimulatorBased

INCLUDEPATH += $$PWD/../simulatorBase
DEPENDPATH += $$PWD/../simulatorBase


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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin71/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin71/ -lcommond

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common


