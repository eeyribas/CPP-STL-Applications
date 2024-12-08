QT -= gui

CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    datapacket.cpp \
    base.cpp \
    derived1.cpp \
    derived2.cpp

HEADERS += \
    parameters.h \
    customqueue.h \
    datapacket.h \
    base.h \
    derived1.h \
    derived2.h
