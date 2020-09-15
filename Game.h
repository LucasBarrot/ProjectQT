#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "Generation_World.h"
#include "Player.h"
#include "Update.h"
#include "Projectil.h"
#include "UI.h"
#include "Inventory.h"
#include "ListWeapon.h"


class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    void mouseMoveEvent(QMouseEvent * event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    bool get_verifRotationCaracter();

    QGraphicsScene * scene;
    Generation_World * world;
    Player * player;
    UI * ui;
    Inventory * inventory;
    ListWeapon * listWeapon;

    QVector<Projectil*> tabProjectil;

    std::set<int> mousePressed_;

    double fps;

    //height and width screen
    double heightScreen;
    double widthScreen;

private:
    double orientationWeapon;
    bool verifRotationCaractere = true;

    bool verifLeftClick;

    //set first weapon
    void addFirstWeaponToInventory();
};

#endif // GAME_H
