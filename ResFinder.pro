#-------------------------------------------------
#
# Project created by QtCreator 2018-02-20T10:58:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ResFinder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filedata.cpp \
    Level.cpp \
    trigger.cpp \
    resfitter.cpp \
    snr.cpp

HEADERS  += mainwindow.h \
    filedata.h \
    resfitter.h

FORMS    += mainwindow.ui
