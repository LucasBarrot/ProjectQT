#include "Room.h"
#include "Game.h"

Room::Room(int x, int y, int width, int height) :  QPolygonF(QRectF(x,y,width,height))
{
    this->height = height;
    this->width = width;

    this->x = x;
    this->y = y;

    this->ground_x =x+16;
    this->ground_y =y+16;

    ground_height = height - 16*2;
    ground_width  = width - 16*2;

    //set all grounds of rooms
}

void Room::add_ground(QGraphicsScene *scene){
    for(float xg=ground_x; xg< ground_x+ground_width; xg+=16){
        for(float yg=ground_y; yg < ground_y+ground_height; yg+=16){
            Ground * tile = new Ground();
            scene->addItem(tile);
            tile->setPos(xg,yg);
        }
    }

}
void Room::add_walls(QGraphicsScene *scene){
    //QRectF rect(ground_x,ground_y,ground_height,ground_width);
    Wall * wall = new Wall(4);
    scene->addItem(wall);
    wall->setPos(this->x,y);

    wall = new Wall(3);
    scene->addItem(wall);
    wall->setPos(this->x+width-16,y);

    wall = new Wall(5);
    scene->addItem(wall);
    wall->setPos(this->x+width-16,this->y+height-16);

    wall = new Wall(6);
    scene->addItem(wall);
    wall->setPos(x,this->y+height-16);

/*
    for(float yw=this->y+16; yw<this->y+height-16; y+=16){
        Wall * wall = new Wall(2);
        scene->addItem(wall);
        wall->setPos(this->x,yw);
        wall = new Wall(2);
        scene->addItem(wall);
        wall->setPos(this->x+width-16,yw);
   }*/
}



QPointF Room::middle_top_point(){
    QPointF point = QPointF(x+width/2, y);
    return point;
}

QPointF Room::middle_left_point(){
    QPointF point = QPointF(x, y+height/2);
    return point;

}

QPointF Room::middle_bottom_point(){
    QPointF point = QPointF(x+width/2, y+height);
    return point;
}

QPointF Room::middle_right_point(){
    QPointF point = QPointF(x+width, y+height/2);
    return point;

}

int Room::which_enter(QPointF point)
{
    if (middle_top_point() == point)
        return 0;

    else if (middle_left_point() == point)
        return 1;

    else if (middle_bottom_point() == point)
        return 2;

    else if (middle_right_point() == point)
        return 3;
}

void Room::block_enter_of_this_point(QPointF point){
    if(enter_side[0]==0){
        if (point == middle_top_point())
            enter_side[0]=1;
    }
    if(enter_side[1]==0){
        if (point == middle_left_point())
            enter_side[1]=1;
    }
    if(enter_side[2]==0){
        if (point == middle_bottom_point())
            enter_side[2]=1;
    }
    if(enter_side[3]==0){
        if (point == middle_right_point())
            enter_side[3]=1;
    }
}

void Room::block_enter_side(int side){
    enter_side[side]=1;
}


int * Room::get_enter_sides(){
    return enter_side;
}



