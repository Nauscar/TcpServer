#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T13:15:06
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TCP-Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    applicationui.cpp \
    tcpserver.cpp

HEADERS += \
    applicationui.h \
    tcpserver.h
