#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T12:25:08
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = wowhttp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    FakeHTTPServer.cpp

HEADERS += \
    FakeHTTPServer.h

OTHER_FILES += \
    Procfile
