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
    src/views/mainwindow.cpp \
    src/model/classwriter.cpp \
    src/utils/LogManager.cpp \
    ui/fieldmemberwindow.cpp \
    ui/methodview.cpp

HEADERS  += src/views/mainwindow.hpp \
    src/utils/LogManager.hpp \
    src/utils/FileManager.hpp \
    src/model/classdefinition.hpp \
    src/model/classwriter.hpp \
    src/model/fieldmember.hpp \
    src/model/range.hpp \
    ui/fieldmemberwindow.hpp \
    src/model/parameter.hpp \
    src/model/method.hpp \
    ui/methodview.hpp

FORMS    += ui/mainwindow.ui \
    ui/fieldmemberwindow.ui \
    ui/methodview.ui

OTHER_FILES +=

RESOURCES += \
    resources/resources.qrc
