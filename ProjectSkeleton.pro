#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T18:50:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectSkeleton
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


SOURCES += main.cpp \
    state.cpp \
    actor.cpp \
    player.cpp \
    bullet.cpp \
    weapon.cpp \
    gameloop.cpp \
    health.cpp \
    score.cpp \
    mainmenu.cpp \
    enemy.cpp \
    enemyone.cpp \
    enemytwo.cpp \
    enemythree.cpp \
    enemyfour.cpp

HEADERS  += \
    state.h \
    actor.h \
    player.h \
    bullet.h \
    weapon.h \
    gameloop.h \
    health.h \
    score.h \
    mainmenu.h \
    enemy.h \
    enemyone.h \
    enemytwo.h \
    enemythree.h \
    enemyfour.h

FORMS    +=

RESOURCES += \
    images.qrc
