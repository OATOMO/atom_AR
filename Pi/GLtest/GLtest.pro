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
