#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T09:53:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wall.cpp \
    snake.cpp \
    food.cpp \
    controller.cpp \
    end.cpp \

HEADERS  += mainwindow.h \
    wall.h \
    snake.h \
    food.h \
    controller.h \
    end.h \

FORMS    += mainwindow.ui
