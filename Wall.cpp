#include "Wall.h"
#include <QGraphicsRectItem>
#include <QRectF>

Wall::Wall(int x, int y, int width, int length) : QObject(), QGraphicsRectItem(){

    setRect(x,y,width,length);
    /***
    // add right collider
    ColliderLeft.setRect(0,0, 10,length);

    // add right collider
    ColliderRight.setRect(0+width-10,0, 10,length);

    // add top collider
    ColliderTop.setRect(0,0, width,10);

    // add bottom collider
    ColliderBottom.setRect(0,0+length-10, width,10);
    ***/
}
