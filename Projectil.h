#ifndef PROJECTIL_H
#define PROJECTIL_H

#include <QGraphicsPixmapItem>

#include "Wall.h"

class Projectil: public QGraphicsPixmapItem{
public:
    Projectil(double angle);
    void moveProjectil();
private:
    double angle;
};

#endif // PROJECTIL_H
