#include "Bridge.h"
#include "Ground.h"
#include "Wall.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <time.h>


Bridge::Bridge(double argHeightWall, double agrHeightBridge)
{
    group = new QGraphicsItemGroup();
    width = agrHeightBridge;
    heightWall = argHeightWall;
}

void Bridge::ConstructBridge(int lengthBridge, int nSide)
{
    //set height
    length = lengthBridge;
    //create ground

    //create wall
    Wall * wall_1;
    Wall * wall_2;
    if(nSide == 0 || nSide == 2){
        wall_1 = new Wall(heightWall, length, 2);
        wall_2 = new Wall(heightWall, length, 2);
        createGround(width, length);
        wall_2->setPos(width - heightWall,0);
    }
    else {
        wall_1 = new Wall(length, heightWall, 0);
        wall_2 = new Wall(length, heightWall, 0);
        createGround(length, width);
        wall_2->setPos(0, width - heightWall);
    }

    wall_1->setPos(0,0);
    group->addToGroup(wall_1);

    group->addToGroup(wall_2);
    group->setParentItem(this);

}

double Bridge::get_length()
{
    return length;
}

double Bridge::get_width()
{
    return width;
}

void Bridge::destructionBridge(){
    delete  this;
}

void Bridge::createGround(int xSize, int ySize)
{
    int xSizeOneBlock = 16;
    int ySizeOneBlock = 16;

    int nXBlock = abs(xSize) / xSizeOneBlock;
    int nYBlock = abs(ySize) / ySizeOneBlock;

    int xPositionNextBlock = 0;
    int yPositionNextBlock = 0;

    for(int i = 0; i < nXBlock; i++){
        for(int y = 0; y < nYBlock; y++){
            Ground * ground = new Ground(xSizeOneBlock, xSizeOneBlock, rand()%20, rand()%4);
            ground->setPos(this->pos().x() + xPositionNextBlock, this->pos().y() + yPositionNextBlock);
            group->addToGroup(ground);
            yPositionNextBlock += ySizeOneBlock;
        }
        xPositionNextBlock += xSizeOneBlock;
        yPositionNextBlock = 0;
    }
}
