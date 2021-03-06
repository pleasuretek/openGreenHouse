#-------------------------------------------------
#
# Project created by QtCreator 2011-12-30T11:15:48
#
#-------------------------------------------------

QT       += core gui sql svg

TARGET = QHardwareKontrol
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    QAsyncSerial.cpp \
    AsyncSerial.cpp \
    sensorgraph.cpp \
    sensors.cpp \
    timer.cpp \
    target.cpp \
    tincrement.cpp \
    relay.cpp \
    tracker.cpp \
    entry.cpp

HEADERS  += mainwindow.h \
    QAsyncSerial.h \
    AsyncSerial.h \
    sensorgraph.h \
    sensors.h \
    timer.h \
    target.h \
    tincrement.h \
    relay.h \
    tracker.h \
    entry.h

FORMS    += mainwindow.ui \
    sensorgraph.ui \
    sensors.ui \
    timer.ui \
    target.ui \
    tincrement.ui \
    relay.ui \
    tracker.ui \
    entry.ui

LIBS += -L/usr/include \
    -lboost_system \
    -lboost_thread \
    -lboost_date_time \
    -lqwt-qt4
