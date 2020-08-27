#include "Bridge.h"
#include "Ground.h"
#include "Wall.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <time.h>

Bridge::Bridge()
{
    group = new QGraphicsItemGroup();
}

void Bridge::Constructor(int lengthBridge)
{
    //set height
    length = lengthBridge;
    //create ground
    createGround(width, length);
    //create wall
    Wall * wall_1 = new Wall(10, length);
    wall_1->setPos(0,0);
    group->addToGroup(wall_1);
    Wall * wall_2 = new Wall(10, length);
    wall_2->setPos(width - 10,0);
    group->addToGroup(wall_2);
    scene()->addItem(group);

}

double Bridge::get_length()
{
    return length;
}

double Bridge::get_width()
{
    return width;
}

void Bridge::createGround(int xSize, int ySize)
{
    int xSizeOneBlock = 10;
    int ySizeOneBlock = 10;

    int nXBlock = abs(xSize) / xSizeOneBlock;
    int nYBlock = abs(ySize) / ySizeOneBlock;

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
