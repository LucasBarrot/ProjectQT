#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsRectItem>

class Wall : public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Wall(int x,int y, int width, int length);

private:
QGraphicsRectItem ColliderLeft;
QGraphicsRectItem ColliderRight;
QGraphicsRectItem ColliderTop;
QGraphicsRectItem ColliderBottom;

signals:

};

#endif // WALL_H
