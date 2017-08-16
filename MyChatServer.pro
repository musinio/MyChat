QT += core
QT -= gui
QT += sql

CONFIG += c++11

TARGET = MyChatServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cxx \
    DataBase.cxx

HEADERS += \
    DataBase.h

QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas
