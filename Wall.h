#ifndef WALL_H
#define WALL_H

#include <QGraphicsRectItem>

class Wall: public QGraphicsRectItem{
public:
    Wall(int lenght, int height, int nSide);
};

#endif // WALL_H
