#-------------------------------------------------
#
# Project created by QtCreator 2017-07-27T23:09:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = toukei-qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/libtoukei/release/ -ltoukei
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/libtoukei/debug/ -ltoukei
else:unix: LIBS += -L$$PWD/../build/libtoukei/ -ltoukei

INCLUDEPATH += $$PWD/../libtoukei
DEPENDPATH += $$PWD/../libtoukei

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/libtoukei/release/libtoukei.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/libtoukei/debug/libtoukei.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build/libtoukei/release/toukei.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build/libtoukei/debug/toukei.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build/libtoukei/libtoukei.a

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += jansson

unix: PKGCONFIG += sqlite3
