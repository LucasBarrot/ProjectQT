#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "Generation_World.h"
#include "Player.h"
#include "Update.h"
#include "Projectil.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    void mouseMoveEvent(QMouseEvent * event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    QGraphicsScene * scene;
    Generation_World * world;
    Player * player;

    QVector<Projectil*> tabProjectil;

    bool verifRotationCaractere = true;

    double fps;

private:
    double orientationWeapon;
};

#endif // GAME_H
