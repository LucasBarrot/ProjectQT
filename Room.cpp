#include "Room.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <time.h>


Room::Room(){
    group = new QGraphicsItemGroup();
    ifRoomTop = false;
    ifRoomRight = false;
    ifRoomBottom = false;
    ifRoomLeft = false;
    nSideNotRoom = 4;
}

void Room::constructor(int nSideGate, std::string typeOfRoom)
{
    type = typeOfRoom;

    if(type.compare("spawn") == 0){
        heightRoom = 200;
        widthRoom = 200;
    }
    else if(type.compare("test") == 0){
        heightRoom = 200;
        widthRoom = 200;
    }
    else if(type.compare("monsterRoom") == 0){
        heightRoom = 200;
        widthRoom = 200;
    }
    else if(type.compare("giftRoom") == 0){
        heightRoom = 120;
        widthRoom = 120;
    }
    else if(type.compare("bossRoom") == 0){
        heightRoom = 300;
        widthRoom = 300;
    }

    //add ground
    createGround(heightRoom, widthRoom);
    //corner
    setCorner(0,0);
    setCorner(widthRoom - 10,0);
    setCorner(widthRoom - 10,heightRoom - 10);
    setCorner(0,heightRoom - 10);


    //wall
    //wall top
    wall_0 = new Wall( widthRoom - 20 ,10);
    wall_0->setPos(10,0);
    group->addToGroup(wall_0);
    //wall right
    wall_1 = new Wall(10, heightRoom - 20);
    wall_1->setPos(widthRoom - 10,10);
    //wall_1->setPen(Qt::NoPen);
    group->addToGroup(wall_1);
    //wall down
    wall_2 = new Wall(widthRoom - 20, 10);
    wall_2->setPos(10,heightRoom - 10);
    group->addToGroup(wall_2);
    //wall left
    wall_3 = new Wall(10, heightRoom - 20);
    wall_3->setPos(0,10);
    group->addToGroup(wall_3);

    if (nSideGate >= 0) {
        if(nSideGate == 0){
            group->removeFromGroup(wall_0);
            setGate(nSideGate, widthRoom - 20,10,10,0, false);
        }
        if(nSideGate == 1){
            group->removeFromGroup(wall_1);
            setGate(nSideGate, heightRoom - 20,10,widthRoom - 10,10, false);
        }
        if(nSideGate == 2){
            group->removeFromGroup(wall_2);
            setGate(nSideGate, widthRoom - 20,10,10,heightRoom - 10, false);
        }
        if(nSideGate == 3){
            group->removeFromGroup(wall_3);
            setGate(nSideGate, heightRoom - 20,10,0,10, false);
        }
    }

    //add to the scene
    scene()->addItem(group);

}

void Room::update_side_gate(int nSide, int xCoordPar, int yCoordPar)
{
    if(nSide == 0){
        //scene()->removeItem(group);
        group->removeFromGroup(wall_0);
        scene()->removeItem(wall_0);
        delete wall_0;
        setGate(nSide, widthRoom - 20,10,10+xCoordPar,0+yCoordPar, true);
    }
    if(nSide == 1){
        group->removeFromGroup(wall_1);
        scene()->removeItem(wall_1);
        delete wall_1;
        setGate(nSide, heightRoom - 20,10,widthRoom - 10 +xCoordPar,10+yCoordPar, true);
    }
    if(nSide == 2){
        group->removeFromGroup(wall_2);
        scene()->removeItem(wall_2);
        delete wall_2;
        setGate(nSide, widthRoom - 20,10,10+xCoordPar,heightRoom - 10 +yCoordPar, true);
    }
    if(nSide == 3){
        group->removeFromGroup(wall_3);
        scene()->removeItem(wall_3);
        delete wall_3;
        setGate(nSide, heightRoom - 20,10,0+xCoordPar,10+yCoordPar, true);
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

    return NULL;
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
    int xSizeOneBlock = 10;
    int ySizeOneBlock = 10;

    int nXBlock = xSize / xSizeOneBlock;
    int nYBlock = ySize / ySizeOneBlock;


    int xPositionNextBlock = 0;
    int yPositionNextBlock = 0;

    for(int i = 0; i < nXBlock; i++){
        for(int y = 0; y < nYBlock; y++){
            Ground * ground = new Ground(xSizeOneBlock, xSizeOneBlock, rand()%4);
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
    int xSizeGate = (xSize - 80)/2;
    if(nSide == 1 || nSide == 3){
        gate_1 = new Wall(ySize, xSizeGate);
        gate_2 = new Wall(ySize, xSizeGate);
        gate_2->setPos(xCoord,yCoord + xSize - xSizeGate);

    }
    else {
        gate_1 = new Wall(xSizeGate, ySize);
        gate_2 = new Wall(xSizeGate, ySize);
        gate_2->setPos(xCoord + xSize - xSizeGate, yCoord);
    }
    gate_1->setPos(xCoord,yCoord);

    if(update == true){
        scene()->addItem(gate_1);
        scene()->addItem(gate_2);
    }
    else{
        group->addToGroup(gate_1);
        group->addToGroup(gate_2);
    }
}

void Room::setCorner(int xCoord, int yCoord){
    Wall * corner = new Wall(sizeCorner,sizeCorner);
    corner->setPos(xCoord,yCoord);
    group->addToGroup(corner);
}




