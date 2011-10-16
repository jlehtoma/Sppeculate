#-------------------------------------------------
#
# Project created by QtCreator 2011-10-08T20:49:07
#
#-------------------------------------------------

QT       += core gui

TARGET = Sppeculate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trainingset.cpp \
    configdialog.cpp

HEADERS  += mainwindow.h \
    trainingset.h \
    configdialog.h

FORMS    += mainwindow.ui \
    configdialog.ui

RESOURCES += \
    sppeculate.qrc

# The application version
VERSION = 0.0.1

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"



