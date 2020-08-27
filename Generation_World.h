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

class Generation_World: public QGraphicsRectItem{
public:
    Generation_World();
    void generate();
private:
    int numberRoom;
    int numberRoomHigh = 10;
    int numberRoomLow = 5;
    int addBridge(int checkNumberBridge, int nRoomRandom, int xDisplacement, int yDisplacement,int height);
    QVector<Room*>  tabRoomFree;
    //QVector<Room*> tabRoomFull;
    QVector<Bridge*>  tab_bridge;
    bool verifCollider(QList<QGraphicsItem *> list_Collider);
};

#endif // GENERATION_WORLD_H
