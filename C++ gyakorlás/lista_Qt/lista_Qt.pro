TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    lista.cpp

HEADERS += \
    lista.h

