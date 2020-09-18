#ifndef BRIDGE_H
#define BRIDGE_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsView>


class Bridge: public QGraphicsItemGroup{
public:
    Bridge(double heightWall, double heightBridge);
    void ConstructBridge(int height, int nSide);
    double get_length();
    double get_width();
    QGraphicsItemGroup * group;

    //destrution bridge
    void destructionBridge();


private:
    double width;
    double length;
    double heightWall;
    void createGround(int xSize, int ySize);
};

#endif // BRIDGE_H
