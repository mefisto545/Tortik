#-------------------------------------------------
#
# Project created by QtCreator 2018-02-20T10:58:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

QMAKE_CFLAGS_RELEASE += -O2
QMAKE_CFLAGS += -Wall -Wextra -Wfloat-equal -Wundef -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wshadow -Wdiv-by-zero
QMAKE_CFLAGS += -isystem $$[QT_INSTALL_HEADERS]

QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS += -Wall -Wextra -Wfloat-equal -Wundef -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wshadow -Wdiv-by-zero
QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]

TARGET = ResFinder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filedata.cpp \
    Level.cpp \
    trigger.cpp \
    resfitter.cpp \
    snr.cpp \
    qcustomplot.cpp \
    als.cpp

HEADERS  += mainwindow.h \
    filedata.h \
    resfitter.h \
    qcustomplot.h \
    als.h

FORMS    += mainwindow.ui
