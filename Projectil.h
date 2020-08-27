#ifndef PROJECTIL_H
#define PROJECTIL_H

#include <QGraphicsPixmapItem>

class Projectil: public QGraphicsPixmapItem{
public:
    Projectil();
    void moveProjectil();
};

#endif // PROJECTIL_H
