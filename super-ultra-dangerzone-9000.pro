#-------------------------------------------------
#
# Project created by QtCreator 2013-08-28T20:59:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = super-ultra-dangerzone-9000
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    game.cpp \
    playership.cpp \
    enemyship.cpp \
    bullet.cpp \
    gameobject.cpp \
    linearbullet.cpp \
    dummyship.cpp \
    explosion.cpp \
    level.cpp \
    gameevent.cpp \
    zigzagship.cpp \
    spawnership.cpp \
    straightship.cpp \
    divership.cpp \
    sideshotship.cpp

HEADERS  += mainwindow.h \
    game.h \
    gameobject.h \
    playership.h \
    enemyship.h \
    bullet.h \
    linearbullet.h \
    explosion.h \
    level.h \
    gameevent.h

FORMS    +=

RESOURCES += \
    images.qrc
