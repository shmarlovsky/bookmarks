#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T14:59:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookMarks
TEMPLATE = app


SOURCES += main.cpp\
    tray.cpp \
    bookmark.cpp

HEADERS  += \
    tray.h \
    bookmark.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    res.qrc
