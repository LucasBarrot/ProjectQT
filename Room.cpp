#include "Room.h"
#include <QPointF>
#include <QDebug>

Room::Room(int x, int y, int width, int height) : QObject(), QGraphicsPolygonItem(){
    this->height = height;
    this->width = width;
    this->x = x;
    this->y = y;

    QPolygonF poly_out, poly_in, poly_enter;
    poly_out << QPointF(x, y);
    poly_out << QPointF(x, y+height);
    poly_out << QPointF(x+width, y+height);
    poly_out << QPointF(x+width, y);


    room = poly_out;
    setPolygon(room);

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

void Room::block_enter_side(QPointF point_side){
    if(enter_side[0]==0){
        if (point_side == middle_top_point())
            enter_side[0]=1;
    }
    if(enter_side[1]==0){
        if (point_side == middle_left_point())
            enter_side[1]=1;
    }
    if(enter_side[2]==0){
        if (point_side == middle_bottom_point())
            enter_side[2]=1;
    }
    if(enter_side[3]==0){
        if (point_side == middle_right_point())
            enter_side[3]=1;
    }
}

QPolygonF Room::get_room(){
    return room;
}

int * Room::get_enter_sides(){
    return enter_side;
}
