TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    kalmanfilter.cpp \
    matrix.cpp \
    radardata.cpp \
    inputdata.cpp

HEADERS += \
    kalmanfilter.h \
    matrix.h \
    radardata.h \
    inputdata.h

