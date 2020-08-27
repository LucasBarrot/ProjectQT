#include "Ground.h"

#include <QBrush>
#include <QPainter>
#include <string>
#include <iostream>

Ground::Ground(int Height, int Weight, int random)
{
    QImage * img;
    if(random == 1){
        img = new QImage(":/Source/Source/Image/Ground_1.png");
    }
    else if(random == 2){
        img = new QImage(":/Source/Source/Image/Ground_2.png");
    }
    else if(random == 3){
        img = new QImage(":/Source/Source/Image/Ground_3.png");
    }
    else {
        img = new QImage(":/Source/Source/Image/Ground_4.png");
    }

    QBrush brush(*img);
    setBrush(brush);
    setRect(0,0,Height, Weight);
    setPen(Qt::NoPen);
}
