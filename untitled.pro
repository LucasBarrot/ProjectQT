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
    Chest.cpp \
    Collider.cpp \
    DoorToNextLevel.cpp \
    Enemy.cpp \
    EntityCaracter.cpp \
    EntityWeapon.cpp \
    Game.cpp \
    Generation_World.cpp \
    Ground.cpp \
    Heart.cpp \
    Inventory.cpp \
    ListBoss.cpp \
    ListEnemy.cpp \
    ListWeapon.cpp \
    Menu.cpp \
    Minimap.cpp \
    Pause.cpp \
    Player.cpp \
    Potion.cpp \
    Projectil.cpp \
    RecapGame.cpp \
    Room.cpp \
    SlotWeaponUI.cpp \
    SpawnZone.cpp \
    UI.cpp \
    Update.cpp \
    Wall.cpp \
    Weapon.cpp \
    WeaponOnGround.cpp \
    WeaponPixmap.cpp \
    main.cpp

HEADERS += \
    Bridge.h \
    Chest.h \
    Collider.h \
    DoorToNextLevel.h \
    Enemy.h \
    EntityCaracter.h \
    EntityWeapon.h \
    Game.h \
    Generation_World.h \
    Ground.h \
    Heart.h \
    Inventory.h \
    ListAttackWeapon.h \
    ListBoss.h \
    ListEnemy.h \
    ListWeapon.h \
    Menu.h \
    Minimap.h \
    Pause.h \
    Player.h \
    Potion.h \
    Projectil.h \
    RecapGame.h \
    Room.h \
    SlotWeaponUI.h \
    SpawnZone.h \
    UI.h \
    Update.h \
    Wall.h \
    Weapon.h \
    WeaponOnGround.h \
    WeaponPixmap.h

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
