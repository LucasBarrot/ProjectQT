#include "Ground.h"

#include <QBrush>
#include <QPainter>
#include <string>
#include <iostream>
#include <time.h>
#include <random>

Ground::Ground() : QGraphicsPixmapItem()
{
    double random = rand() % 9;
    //double random2 = rand() % 3;

    QString filename;
    //srand(time(NULL));

    QPixmap img;
    if(random == 1){
        img =QPixmap(":/Source/Source/Image/Ground/Ground_2.png");
    }
    else if(random == 2){
        img =QPixmap(":/Source/Source/Image/Ground/Ground_3.png");
    }
    else if(random == 3){
        img = QPixmap(":/Source/Source/Image/Ground/Ground_4.png");
    }
    else if(random == 4){
        img = QPixmap(":/Source/Source/Image/Ground/Ground_5.png");
    }
    else if(random == 5){
        img =  QPixmap(":/Source/Source/Image/Ground/Ground_6.png");
    }
    else if(random == 6){
        img =  QPixmap(":/Source/Source/Image/Ground/Ground_7.png");
    }
    else if(random == 7){
        img =  QPixmap(":/Source/Source/Image/Ground/Ground_8.png");
    }
    else if(random == 8){
        img =  QPixmap(":/Source/Source/Image/Ground/Ground_9.png");
    }
    else if(random == 9){
        img =  QPixmap(":/Source/Source/Image/Ground/Ground_10.png");
    }
    else {
        img =QPixmap(":/Source/Source/Image/Ground/Ground_1.png");
    }
    setPixmap(img);


    /*
    if(random2 == 1){
        img = img.mirrored(true, false);
    }
    else if(random2 == 2){
        img = img->mirrored(false, true);
    }
    else if(random2 == 3){
        img = img>mirrored(true, true);
    }
    */
}

