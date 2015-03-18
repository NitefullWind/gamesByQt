#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T20:28:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flappyBird
TEMPLATE = app


SOURCES +=\
        map.cpp \
    mainwindow.cpp \
    controller.cpp \
    mainwindow.cpp \
    main.cpp \
    bird.cpp

HEADERS  += map.h \
    controller.h \
    mainwindow.h \
    bird.h

RESOURCES += \
    image.qrc
