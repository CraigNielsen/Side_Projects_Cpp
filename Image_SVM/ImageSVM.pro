#-------------------------------------------------
#
# Project created by QtCreator 2015-05-21T18:23:54
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ImageSVM
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    trainerobject.cpp \
    file_io.cpp \
    cbn_consoleoutput.cpp \
    consoleOutputs.cpp
QMAKE_CXXFLAGS += -std=c++11
LIBS += `pkg-config opencv --libs`
LIBS +=     -lboost_system\


HEADERS += \
    trainerobject.h \
    file_io.h \
    cbn_consoleoutput.h
