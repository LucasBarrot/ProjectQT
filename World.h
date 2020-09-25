#ifndef GENERATION_WORLD_H
#define GENERATION_WORLD_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QGraphicsItemGroup>
#include <string>

#include "Room.h"
#include "Collider.h"
#include "Enemy.h"
#include <vector>
#include <array>
#include "Hallway.h"

using namespace std;

class World: public QObject , public QGraphicsPolygonItem{
public:
    World(Room * room1, Room * room2);
    QPolygonF get_poly();
    void add_room_to_memory(Room * room);
    void connect(Room *room);
    Hallway build_hallway(QPointF point1, QPointF point2, int enter_side);

    bool intersect(QPolygonF);
    vector<QList<QPointF>> get_network_free_points();
    vector<Hallway > hallways_list;
    QList<Room *> rooms_in_net; //contient les chambre avec leurs coordonnées
    //vector<QRectF> rect_h;
    //vector<QRectF> rect_v;
    ////////////////////////////////////////////////////

    //void generate();

    //get heightWall, sizeCorner (same)
    //double get_heightWall();

    //tab of all room that are available
    //QVector<Room*>  tabRoom;

    //tab of all bridge
    //QVector<Bridge*>  tab_bridge;
    //bool verifCollider(QList<QGraphicsItem *> list_Collider);

private:

    QPolygonF network;
    ///////////////////////////////////////////////////////
    //number of room in generation
    //int numberRoom;
    //number maximum of room
    //int numberRoomHigh = 10;
    //number minimum of room
    //int numberRoomLow = 5;

    //set the height of the wall
    // double heightWall;
    //set the lenght of the bridge
    //double heightBridge;

    //tab of all room that are available
    //QVector<Room*>  tabRoomFree;

    //bridge
    //add a new bridge
    //int addBridge(int nSide, int checkNumberBridge, int nRoomRandom, int xDisplacement, int yDisplacement,int height);

};

#endif // GENERATION_WORLD_H
