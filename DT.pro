#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T12:19:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DT
TEMPLATE = app


SOURCES += main.cpp\
        mainform.cpp \
    edge.cpp \
    algorithms.cpp \
    sortbyxasc.cpp

HEADERS  += mainform.h \
    edge.h \
    algorithms.h \
    sortbyxasc.h

FORMS    += mainform.ui
