QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgProcess
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        showpicture.cpp \
        startanimal.cpp \
        imgprocesscenterwidget.cpp

HEADERS  += mainwindow.h \
        showpicture.h \
        startanimal.h \
        imgprocesscenterwidget.h

FORMS    += mainwindow.ui \
        showpicture.ui \
        imgprocesscenterwidget.ui

RESOURCES += img.qrc

RC_FILE += imgprocess.rc
