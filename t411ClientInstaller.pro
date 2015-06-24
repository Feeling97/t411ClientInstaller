QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = t411ClientInstaller
TEMPLATE = app

QMAKE_CFLAGS_RELEASE += -Os -mtune=generic -fomit-frame-pointer -fno-rtti -fno-exceptions -fno-keep-inline-dllexport -m32
QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE
QMAKE_LFLAGS_RELEASE += -s

SOURCES += main.cpp\
        mainwindow.cpp \
    installer.cpp \
    filedownloader.cpp \
    aboutlabel.cpp \
    options.cpp

HEADERS  += mainwindow.h \
    ui_mainwindow.h \
    installer.h \
    filedownloader.h \
    aboutlabel.h \
    options.h

RESOURCES += resources.qrc

RC_FILE += resources.rc
