#include "Wall.h"

#include <QBrush>
#include <QPainter>

Wall::Wall(int lenght, int height)
{
    QImage * img = new QImage(":/Source/Source/Image/Wall_1.png");
    QBrush brush(*img);
    setBrush(brush);
    setRect(0,0,lenght, height);
    setPen(Qt::NoPen);
}
