QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = t411ClientInstaller
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    installer.cpp \
    filedownloader.cpp \
    aboutlabel.cpp

HEADERS  += mainwindow.h \
    ui_mainwindow.h \
    installer.h \
    filedownloader.h \
    aboutlabel.h

RESOURCES += resources.qrc

RC_FILE += resources.rc
