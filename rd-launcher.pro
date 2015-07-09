#-------------------------------------------------
#
# Project created by QtCreator 2015-07-08T23:28:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rd-launcher
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    rdpoptions.cpp \
    rdesktoplauncher.cpp

HEADERS  += maindialog.h \
    rdpoptions.h \
    rdesktoplauncher.h

FORMS    += maindialog.ui

RESOURCES += \
    rc.qrc
