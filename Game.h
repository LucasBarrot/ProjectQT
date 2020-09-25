#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "World.h"
#include "Player.h"
#include "Update.h"
#include "Projectil.h"
#include "UI.h"

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
    World * world;
    Player * player;
    UI * ui;

    QVector<Projectil*> tabProjectil;

    std::set<int> mousePressed_;

    double fps;

private:
    double orientationWeapon;
    bool verifRotationCaractere = true;

    bool verifLeftClick;
};

#endif // GAME_H
