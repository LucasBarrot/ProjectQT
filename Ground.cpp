#include "Ground.h"

#include <QBrush>
#include <QPainter>
#include <string>
#include <iostream>
#include <time.h>
#include <random>

Ground::Ground(int Height, int Weight, int random, int random_2)
{
    //srand(time(NULL));

    QImage * img;
    if(random == 1){
        img = new QImage(":/Source/Source/Image/Ground/Ground_2.png");
    }
    else if(random == 2){
        img = new QImage(":/Source/Source/Image/Ground/Ground_3.png");
    }
    else if(random == 3){
        img = new QImage(":/Source/Source/Image/Ground/Ground_4.png");
    }
    else if(random == 4){
        img = new QImage(":/Source/Source/Image/Ground/Ground_5.png");
    }
    else if(random == 5){
        img = new QImage(":/Source/Source/Image/Ground/Ground_6.png");
    }
    else if(random == 6){
        img = new QImage(":/Source/Source/Image/Ground/Ground_7.png");
    }
    else if(random == 7){
        img = new QImage(":/Source/Source/Image/Ground/Ground_8.png");
    }
    else if(random == 8){
        img = new QImage(":/Source/Source/Image/Ground/Ground_9.png");
    }
    else if(random == 9){
        img = new QImage(":/Source/Source/Image/Ground/Ground_10.png");
    }
    else {
        img = new QImage(":/Source/Source/Image/Ground/Ground_1.png");
    }



    if(random_2 == 1){
        *img = img->mirrored(true, false);
    }
    else if(random_2 == 2){
        *img = img->mirrored(false, true);
    }
    else if(random_2 == 3){
        *img = img->mirrored(true, true);
    }
    *img = img->scaled(Height, Weight);
    QBrush brush(*img);
    setBrush(brush);
    setRect(0,0,Height, Weight);
    setPen(Qt::NoPen);
}

