QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    boardmodel.cpp \
    boardv1.cpp \
    serialport.cpp

HEADERS += \
    boardmodel.h \
    boardv1.h \
    serialport.h
