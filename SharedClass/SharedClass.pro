QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    baseclass.cpp \
    shared.cpp

HEADERS += \
    baseclass.h \
    shared.h
