#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <string>
#include <iostream>

#include "Ground.h"
#include "Wall.h"

class Room: public QGraphicsItemGroup{

 public:
    Room(double heightWall, double heightBridge);
    void constructor(int nSideGate, std::string typeOfRoom);
    void update_side_gate(int nSide, int xCoordPar, int yCoordPar);

    int get_nSideNotRoom();
    bool get_ifRoom(int nSide);
    void set_ifRoom(int nSide);

    double get_height();
    double get_width();
    std::string get_type();

    QGraphicsItemGroup * group;


private:
    double heightRoom;
    double widthRoom;
    double sizeCorner;
    double sizeWallHeight;

    double heightBridge;

    //define the type of room
    std::string type;

    Wall * wall_0;
    Wall * wall_1;
    Wall * wall_2;
    Wall * wall_3;

    bool ifRoomTop, ifRoomRight, ifRoomBottom, ifRoomLeft;
    int nSideNotRoom;

    //function to create obstacle
    void createGround(int xSize, int ySize);
    void setGate(int nSide, int xSize, int ySize, int xCoord, int yCoord, bool update);
    void setCorner(int xCoord, int yCoord, int nSide);
};

#endif // ROOM_H
