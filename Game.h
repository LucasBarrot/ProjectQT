#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include "Player.h"
#include "Wall.h"

class Game : public QGraphicsView
{
public:
    Game(QWidget * parent = nullptr);

    QGraphicsScene * scene;
    Player * player;


signals:

};

#endif // GAME_H
