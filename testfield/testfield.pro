CONFIG += c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testfield
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# include Breakpad
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../breakpad/release/ -lbreakpad
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../breakpad/debug/ -lbreakpad
else:unix: LIBS += -L$$OUT_PWD/../breakpad/ -lbreakpad

INCLUDEPATH += $$PWD/../breakpad
DEPENDPATH += $$PWD/../breakpad

QMAKE_LFLAGS += -INCREMENTAL:NO -Debug
#QMAKE_CXXFLAGS += -Zi -D__USE_MINGW_ANSI_STDIO
#LIBS=-lws2_32
QMAKE_LFLAGS_RELEASE += -debug -opt:ref

# Define app version and name for Breakpad
VERSION = 1.0.0.0

# Define the preprocessor macro to get the application version in our application
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
