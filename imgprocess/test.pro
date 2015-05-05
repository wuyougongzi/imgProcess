#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T20:17:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgProcess;
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    showpicure.cpp \
    openfiledgl.cpp \
    startanimal.cpp

HEADERS  += mainwindow.h \
    showpicure.h \
    openfiledgl.h \
    startanimal.h

FORMS    += mainwindow.ui \
    showPicure.ui

RESOURCES += \
    img.qrc
