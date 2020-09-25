#ifndef GENERATION_WORLD_H
#define GENERATION_WORLD_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QGraphicsItemGroup>
#include <string>

#include "Room.h"
#include "Bridge.h"
#include "Collider.h"
#include "Enemy.h"

class Generation_World: public QGraphicsRectItem{
public:
    Generation_World();
    void generate();

    //get heightWall, sizeCorner (same)
    double get_heightWall();

    //tab of all room that are available
    QVector<Room*>  tabRoom;

    //tab of all bridge
    QVector<Bridge*>  tab_bridge;
    bool verifCollider(QList<QGraphicsItem *> list_Collider);

    //delete all before creating a new level
    void destructionLevel();

private:
    //number of room in generation
    int numberRoom;
    //number maximum of room
    int numberRoomHigh = 10;
    //number minimum of room
    int numberRoomLow = 5;

    //set the height of the wall
    double heightWall;
    //set the lenght of the bridge
    double heightBridge;

    //tab of all room that are available
    QVector<Room*>  tabRoomFree;

    //bridge
    //add a new bridge
    int addBridge(int nSide, int checkNumberBridge, int nRoomRandom, int xDisplacement, int yDisplacement,int height);

};

#endif // GENERATION_WORLD_H
