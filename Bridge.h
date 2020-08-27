#ifndef BRIDGE_H
#define BRIDGE_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsView>


class Bridge: public QGraphicsItemGroup{
public:
    Bridge();
    void Constructor(int height);
    double get_length();
    double get_width();
    QGraphicsItemGroup * group;

private:
    double width = 100;
    double length;
    void createGround(int xSize, int ySize);
};

#endif // BRIDGE_H
