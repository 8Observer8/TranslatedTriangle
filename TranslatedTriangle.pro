#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T09:46:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TranslatedTriangle
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    Triangle.cpp \
    Scene.cpp

HEADERS  += Dialog.h \
    Triangle.h \
    Scene.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc
