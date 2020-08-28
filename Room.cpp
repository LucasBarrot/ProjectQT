#include "Room.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


Room::Room(double argHeightWall, double argHeightBridge){
    group = new QGraphicsItemGroup();
    ifRoomTop = false;
    ifRoomRight = false;
    ifRoomBottom = false;
    ifRoomLeft = false;
    nSideNotRoom = 4;

    sizeCorner = argHeightWall;
    sizeWallHeight = argHeightWall;
    heightBridge = argHeightBridge;

    setParentItem(NULL);
}

void Room::constructor(int nSideGate, std::string typeOfRoom)
{
    type = typeOfRoom;

    if(type.compare("spawn") == 0){
        heightRoom = 16*13;
        widthRoom = 16*13;
    }
    else if(type.compare("test") == 0){
        heightRoom = 16*13;
        widthRoom = 16*13;
    }
    else if(type.compare("monsterRoom") == 0){
        heightRoom = 16*13;
        widthRoom = 16*13;
    }
    else if(type.compare("giftRoom") == 0){
        heightRoom = 16*9;
        widthRoom = 16*9;
    }
    else if(type.compare("bossRoom") == 0){
        heightRoom = 16*19;
        widthRoom = 16*19;
    }

    //add ground
    createGround(heightRoom, widthRoom);
    //corner
    setCorner(0, 0, 7);
    setCorner(widthRoom - sizeCorner, 0, 1);
    setCorner(widthRoom - sizeCorner,heightRoom - sizeCorner, 3);
    setCorner(0,heightRoom - sizeCorner, 5);


    //wall
    //wall top
    wall_0 = new Wall( widthRoom - sizeCorner * 2 , sizeWallHeight, 0);
    wall_0->setPos(sizeCorner,0);
    group->addToGroup(wall_0);
    //wall right
    wall_1 = new Wall(sizeWallHeight, heightRoom - sizeCorner * 2, 2);
    wall_1->setPos(widthRoom - sizeWallHeight, sizeCorner);
    //wall_1->setPen(Qt::NoPen);
    group->addToGroup(wall_1);
    //wall down
    wall_2 = new Wall(widthRoom - sizeCorner * 2, sizeWallHeight, 4);
    wall_2->setPos(sizeCorner,heightRoom - sizeWallHeight);
    group->addToGroup(wall_2);
    //wall left
    wall_3 = new Wall(sizeWallHeight, heightRoom - sizeCorner * 2, 6);
    wall_3->setPos(0,sizeCorner);
    group->addToGroup(wall_3);

    if (nSideGate >= 0) {
        if(nSideGate == 0){
            group->removeFromGroup(wall_0);
            setGate(nSideGate, widthRoom - sizeCorner * 2,sizeWallHeight, sizeCorner,0, false);
        }
        if(nSideGate == 1){
            group->removeFromGroup(wall_1);
            setGate(nSideGate, heightRoom - sizeCorner * 2,sizeWallHeight,widthRoom - sizeWallHeight,sizeCorner, false);
        }
        if(nSideGate == 2){
            group->removeFromGroup(wall_2);
            setGate(nSideGate, widthRoom - sizeCorner * 2,sizeWallHeight,sizeCorner,heightRoom - sizeWallHeight, false);
        }
        if(nSideGate == 3){
            group->removeFromGroup(wall_3);
            setGate(nSideGate, heightRoom - sizeCorner * 2,sizeWallHeight,0,sizeCorner, false);
        }
    }

    //add to the scene
    scene()->addItem(group);

}

void Room::update_side_gate(int nSide, int xCoordPar, int yCoordPar)
{
    //update the side to put a gate instead of wall
    //first we remove the wall
    //after we the fonction that create gate
    if(nSide == 0){
        //scene()->removeItem(group);
        group->removeFromGroup(wall_0);
        scene()->removeItem(wall_0);
        delete wall_0;
        setGate(nSide, widthRoom - sizeCorner * 2, sizeWallHeight, sizeCorner + xCoordPar, 0+yCoordPar, true);
    }
    if(nSide == 1){
        group->removeFromGroup(wall_1);
        scene()->removeItem(wall_1);
        delete wall_1;
        setGate(nSide, heightRoom - sizeCorner * 2, sizeWallHeight, widthRoom - sizeWallHeight + xCoordPar, sizeCorner + yCoordPar, true);
    }
    if(nSide == 2){
        group->removeFromGroup(wall_2);
        scene()->removeItem(wall_2);
        delete wall_2;
        setGate(nSide, widthRoom - sizeCorner * 2, sizeWallHeight, sizeCorner + xCoordPar, heightRoom - sizeWallHeight +yCoordPar, true);
    }
    if(nSide == 3){
        group->removeFromGroup(wall_3);
        scene()->removeItem(wall_3);
        delete wall_3;
        setGate(nSide, heightRoom - sizeCorner * 2, sizeWallHeight, xCoordPar, sizeCorner + yCoordPar, true);
    }
}

int Room::get_nSideNotRoom()
{
    return nSideNotRoom;
}

double Room::get_height()
{
    return heightRoom;
}

double Room::get_width()
{
    return widthRoom;
}

std::string Room::get_type()
{
    return type;
}

bool Room::get_ifRoom(int nSide)
{
    if(nSide == 0){
        return ifRoomTop;
    }
    else if(nSide == 1){
        return ifRoomRight;
    }
    else if(nSide == 2){
        return ifRoomBottom;
    }
    else if(nSide == 3){
        return ifRoomLeft;
    }

    return false;
}

void Room::set_ifRoom(int nSide)
{
    if(nSide == 0){
         ifRoomTop = true;
    }
    else if(nSide == 1){
        ifRoomRight = true;
    }
    else if(nSide == 2){
        ifRoomBottom = true;
    }
    else if(nSide == 3){
        ifRoomLeft = true;
    }

    nSideNotRoom --;
}




void Room::createGround(int xSize, int ySize){
    //set the size of each cell
    int xSizeOneBlock = 16;
    int ySizeOneBlock = 16;

    //calculate the number of cell we need
    int nXBlock = xSize / xSizeOneBlock;
    int nYBlock = ySize / ySizeOneBlock;

    int xPositionNextBlock = 0;
    int yPositionNextBlock = 0;

    //create a grid of the size of the room, in each cell we put a different image of the ground
    for(int i = 0; i < nXBlock; i++){
        for(int y = 0; y < nYBlock; y++){
            //srand(time(NULL));
            //set the ground with a aleatory number to choose wich image is going to be
            Ground * ground = new Ground(xSizeOneBlock, ySizeOneBlock, rand()%20, rand()%4);
            //set the position of the cell
            ground->setPos(this->pos().x() + xPositionNextBlock, this->pos().y() + yPositionNextBlock);
            group->addToGroup(ground);
            yPositionNextBlock += ySizeOneBlock;
        }
        xPositionNextBlock += xSizeOneBlock;
        yPositionNextBlock = 0;
    }
}

void Room::setGate(int nSide, int xSize, int ySize, int xCoord, int yCoord, bool update)
{
    Wall * gate_1;
    Wall * gate_2;
    int xSizeGate = (xSize - heightBridge)/2 + sizeWallHeight - sizeCorner;
    //position of the gate depending of the side
    if(nSide == 1 || nSide == 3){
        gate_1 = new Wall(ySize, xSizeGate, 2);
        gate_2 = new Wall(ySize, xSizeGate, 2);
        gate_2->setPos(xCoord,yCoord + xSize - xSizeGate);
        if(nSide == 1){
            setCorner( xCoord, yCoord + xSizeGate, 5);
            setCorner(xCoord, yCoord + xSize - xSizeGate - sizeCorner, 7);
        }
        else if(nSide == 3){
            setCorner(xCoord, yCoord + xSizeGate, 3);
            setCorner(xCoord, yCoord + xSize - xSizeGate - sizeCorner, 1);
        }
    }
    else {
        gate_1 = new Wall(xSizeGate, ySize, 0);
        gate_2 = new Wall(xSizeGate, ySize, 0);
        gate_2->setPos(xCoord + xSize - xSizeGate, yCoord);
        if(nSide == 0){
            setCorner(xCoord + xSizeGate, yCoord, 3);
            setCorner(xCoord + xSize - xSizeGate - sizeCorner, yCoord, 5);
        }
        else if(nSide == 2){
            setCorner(xCoord + xSizeGate, yCoord, 1);
            setCorner(xCoord + xSize - xSizeGate - sizeCorner, yCoord, 7);
        }
    }
    gate_1->setPos(xCoord,yCoord);

    //if update is true, the group is already set in the scene, we need to remove it first, add our new gate and add it again to the scene.
    if(update == true){
        scene()->removeItem(group);
        group->addToGroup(gate_1);
        group->addToGroup(gate_2);
        scene()->addItem(group);

    }
    else{
        group->addToGroup(gate_1);
        group->addToGroup(gate_2);
    }
}

void Room::setCorner(int xCoord, int yCoord, int nSide){
    Wall * corner = new Wall(sizeCorner,sizeCorner, nSide);
    corner->setPos(xCoord,yCoord);
    group->addToGroup(corner);
}




