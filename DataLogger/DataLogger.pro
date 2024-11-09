QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    datalogger.cpp \
    datapaths.cpp \
    fileoperations.cpp \
    logger.cpp

HEADERS += \
    datalogger.h \
    datapaths.h \
    fileoperations.h \
    customqueue.h \
    logger.h
