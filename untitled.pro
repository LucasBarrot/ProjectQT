QT       += core gui \
        multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bridge.cpp \
    Collider.cpp \
    Enemy.cpp \
    Entity.cpp \
    Game.cpp \
    Generation_World.cpp \
    Ground.cpp \
    Player.cpp \
    Projectil.cpp \
    Room.cpp \
    SpawnZone.cpp \
    Update.cpp \
    Wall.cpp \
    Weapon.cpp \
    main.cpp

HEADERS += \
    Bridge.h \
    Collider.h \
    Enemy.h \
    Entity.h \
    Game.h \
    Generation_World.h \
    Ground.h \
    Player.h \
    Projectil.h \
    Room.h \
    SpawnZone.h \
    Update.h \
    Wall.h \
    Weapon.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    untitled_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc
