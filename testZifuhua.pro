#-------------------------------------------------
#
# Project created by QtCreator 2015-05-02T23:08:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = testZifuhua
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    zifuhua.cpp
 INCLUDEPATH += /usr/local/include \
                 /usr/local/include/opencv \
                 /usr/local/include/opencv2

 LIBS += /usr/local/lib/libopencv_highgui.so \
         /usr/local/lib/libopencv_core.so    \
         /usr/local/lib/libopencv_imgproc.so

