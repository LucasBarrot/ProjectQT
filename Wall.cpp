#include "Wall.h"

#include <QBrush>
#include <QPainter>

Wall::Wall(int nSide)
{
    QPixmap img;
    if(nSide==1){
        img = QPixmap(":/Source/Source/Image/Wall/Wall_top_1.png");
    }
    else if(nSide == 2){
        img = QPixmap(":/Source/Source/Image/Wall/Wall_side_1.png");
    }
    else if(nSide == 3){
        img = QPixmap(":/Source/Source/Image/Wall/Wall_Corner_Top_Right.png");
    }
    else if(nSide == 4){
        img = QPixmap(":/Source/Source/Image/Wall/Wall_Corner_Top_left_1.png");
    }
    else if(nSide == 5){
        img = QPixmap(":/Source/Source/Image/Wall/Wall_Corner_Bottom_Right_1.png");
    }
    else if(nSide == 6){
        img = QPixmap(":/Source/Source/Image/Wall/Wall_Corner_Bottom_Left_1.png");
    }

    setPixmap(img);
    /*
    else { //test
        img = new QImage(":/Source/Source/Image/Wall_1.png");
    }


    QBrush brush(*img);
    setBrush(brush);
    setRect(0,0,lenght, height);
    setPen(Qt::NoPen);
    */

}
