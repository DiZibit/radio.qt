#-------------------------------------------------
#
# Project created by QtCreator 2016-09-20T01:51:00
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    audiodownloader.cpp \
    audioplayer.cpp

HEADERS  += mainwindow.h \
    audiodownloader.h \
    audioplayer.h

FORMS    += mainwindow.ui
