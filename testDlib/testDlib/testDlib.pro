#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T18:48:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = testDlib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
LIBS += -pthread
CONFIG += link_pkgconfig
PKGCONFIG += x11

SOURCES += main.cpp \
    ../../../dlib/dlib/all/source.cpp

    
LIBS += `pkg-config opencv --libs`
#QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH+= /home/craig/git_repos/dlib/
  
