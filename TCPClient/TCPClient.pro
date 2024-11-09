QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    tcpclient.cpp \
    tcpcomm.cpp \
    shared.cpp \
    communication.cpp

HEADERS += \
    tcpclient.h \
    tcpcomm.h \
    shared.h \
    communication.h
