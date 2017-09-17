#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T13:16:40
#
#-------------------------------------------------

QT       += core gui
QT += opengl



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = load3ds
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myglload3ds.cpp \
    cmodel3ds.cpp

HEADERS  += mainwindow.h \
    myglload3ds.h \
    cmodel3ds.h

LIBS += -lglut -lGL -lGLU -lm  -l3ds

FORMS    += mainwindow.ui
