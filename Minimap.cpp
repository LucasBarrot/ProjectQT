#include "Minimap.h"

#include "Game.h"

extern Game * game;

Minimap::Minimap(double width, double height){
    //divide per scale
    this->setRect(0, 0, width, height);
    setBrush(Qt::yellow);
    setZValue(1);
}
