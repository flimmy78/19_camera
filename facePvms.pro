#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T11:13:02
#
#-------------------------------------------------

QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = facePvms
TEMPLATE = app

SOURCES += main.cpp\
        facepvms.cpp \
    DefineCalendar.cpp \
    DefDateTimeEdit.cpp \
    global.cpp \
    facerecognize.cpp \
    database.cpp

HEADERS  += facepvms.h \
    DefineCalendar.h \
    DefDateTimeEdit.h \
    global.h \
    TSingleIns.h \
    facerecognize.h \
    database.h

FORMS    += facepvms.ui

INCLUDEPATH += $$PWD\include\facerec\
               $$PWD\include\opencv\
               $$PWD\include\opencv\opencv\
               $$PWD\include\opencv\opencv2\
               $$PWD\include\hkvs

LIBS    += -L$$PWD\libs\face\
       -lfaced_lib -lfacea_lib -lfacev_lib \

LIBS+=  $$PWD\libs\opencv\libopencv_core2413.dll.a\
        $$PWD\libs\opencv\libopencv_highgui2413.dll.a\
        $$PWD\libs\opencv\libopencv_imgproc2413.dll.a\
        $$PWD\libs\opencv\libopencv_video2413.dll.a\
        $$PWD\libs\opencv\libopencv_objdetect2413.dll.a\
        $$PWD\libs\opencv\libopencv_ml2413.dll.a\

LIBS+= $$PWD\libs\hkvs\HCNetSDK.lib \
        $$PWD\libs\hkvs\HCAlarm.lib \
        $$PWD\libs\hkvs\HCGeneralCfgMgr.lib \
        $$PWD\libs\hkvs\HCPreview.lib \
        $$PWD\libs\hkvs\gdiplus.lib \
        $$PWD\libs\hkvs\PlayCtrl.lib \
        $$PWD\libs\hkvs\HCCore.lib

RESOURCES += $$PWD\resources\resources.qrc

RC_ICONS += $$PWD\resources\icon.ico

QMAKE_CXXFLAGS +=-msse4.2 -std=c++11 -O2 -w -static
