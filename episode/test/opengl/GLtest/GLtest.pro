#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T21:39:24
#
#-------------------------------------------------

QT       += core gui
QT	+= opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLtest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mygl.cpp

HEADERS  += mainwindow.h \
    mygl.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib \
    /usr/local/lib/libopencv_core.so \
    /usr/local/lib/libopencv_features2d.so \
    /usr/local/lib/libopencv_flann.so \
    /usr/local/lib/libopencv_highgui.so \
    /usr/local/lib/libopencv_imgcodecs.so \
    /usr/local/lib/libopencv_imgproc.so \
    /usr/local/lib/libopencv_ml.so \
    /usr/local/lib/libopencv_objdetect.so \
    /usr/local/lib/libopencv_photo.so \
    /usr/local/lib/libopencv_shape.so \
    /usr/local/lib/libopencv_stitching.so \
    /usr/local/lib/libopencv_superres.so \
    /usr/local/lib/libopencv_videoio.so \
    /usr/local/lib/libopencv_video.so \
    /usr/local/lib/libopencv_videostab.so
