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
    Collider.cpp \
    Enemy.cpp \
    EntityCaracter.cpp \
    EntityWeapon.cpp \
    Game.cpp \
    Ground.cpp \
    Hallway.cpp \
    Player.cpp \
    Projectil.cpp \
    Room.cpp \
    SpawnZone.cpp \
    UI.cpp \
    Update.cpp \
    Wall.cpp \
    Weapon.cpp \
    World.cpp \
    main.cpp

HEADERS += \
    Collider.h \
    Enemy.h \
    EntityCaracter.h \
    EntityWeapon.h \
    Game.h \
    Ground.h \
    Hallway.h \
    Player.h \
    Projectil.h \
    Room.h \
    SpawnZone.h \
    UI.h \
    Update.h \
    Wall.h \
    Weapon.h \
    World.h

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
