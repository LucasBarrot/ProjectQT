#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <string>
#include <iostream>

#include "Ground.h"
#include "Wall.h"
#include "SpawnZone.h"
#include "Enemy.h"

class Room: public QGraphicsItemGroup{

 public:
    //constructor of the room
    Room(double heightWall, double heightBridge);
    void constructor(int nSideGate, std::string typeOfRoom);

    //udpate gate (remove wall to replace it by to small walls)
    void update_side_gate(int nSide, int xCoordPar, int yCoordPar);

    //set close dore when player enter the room
    void closeTheDoor();

    //set spawnZone
    void set_spawnZone(QPointF posSpawnZone, int argSize);

    int get_nSideNotRoom();
    bool get_ifRoom(int nSide);
    void set_ifRoom(int nSide);

    //return size and type of the room
    double get_height();
    double get_width();
    std::string get_type();


    //group of all object in this room
    QGraphicsItemGroup * group;

    //spawn zone
    SpawnZone * spawnZone;

    //destruction room
    void destructionRoom();

private:
    //size room
    double heightRoom;
    double widthRoom;
    //size corner
    double sizeCorner;
    //height wall
    double sizeWallHeight;

    //height of bridge
    double heightBridge;

    //define the type of room
    std::string type;

    //wall of the room(clock wise)
    Wall * wall_0;
    Wall * wall_1;
    Wall * wall_2;
    Wall * wall_3;

    //boolean to know if there are ar room in this direction
    bool ifRoomTop, ifRoomRight, ifRoomBottom, ifRoomLeft;
    int nSideNotRoom;

    //function to create obstacle
    void createGround(int xSize, int ySize);
    void setGate(int nSide, int xSize, int ySize, int xCoord, int yCoord, bool update);
    void setCorner(int xCoord, int yCoord, int nSide);
};

#endif // ROOM_H
