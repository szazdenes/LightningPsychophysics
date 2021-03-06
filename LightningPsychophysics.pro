#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T14:33:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LightningPsychophysics
TEMPLATE = app
DESTDIR = ./bin
OBJECTS_DIR = ./obj
MOC_DIR = ./moc
RCC_DIR = ./rcc
UI_DIR = ./ui


SOURCES += main.cpp\
        mainwindow.cpp \
    imagehandlingform.cpp \
    newsessiondialog.cpp \
    sessionreadydialog.cpp

HEADERS  += mainwindow.h \
    imagehandlingform.h \
    newsessiondialog.h \
    sessionreadydialog.h

FORMS    += mainwindow.ui \
    imagehandlingform.ui \
    newsessiondialog.ui \
    sessionreadydialog.ui
