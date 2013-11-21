#-------------------------------------------------
#
# Project created by QtCreator 2013-11-20T21:51:59
#
#-------------------------------------------------

cache()

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = metacc
TEMPLATE = app


SOURCES += src/main.cpp \
    src/views/mainwindow.cpp

HEADERS  += src/views/mainwindow.hpp \
    src/utils/LogManager.hpp \
    src/utils/FileManager.hpp

FORMS    += ui/mainwindow.ui

OTHER_FILES +=
