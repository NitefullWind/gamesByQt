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
    mainwindow.cpp \
    controller.cpp \
    mainwindow.cpp \
    main.cpp \
    bird.cpp \
    end.cpp \
    pillar.cpp

HEADERS  += \
    controller.h \
    mainwindow.h \
    bird.h \
    end.h \
    pillar.h

RESOURCES += \
    image.qrc
