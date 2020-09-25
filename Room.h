#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <string>
#include <iostream>
#include <QGraphicsScene>
#include "Ground.h"
#include <vector>
#include "SpawnZone.h"
//#include "Enemy.h"
using namespace  std;

class Room : public QPolygonF{
public:
    Room(int x, int y, int width, int height);
    QPointF middle_top_point();
    QPointF middle_left_point();
    QPointF middle_bottom_point();
    QPointF middle_right_point();
    int which_enter(QPointF point);
    int * get_enter_sides();
    void block_enter_of_this_point(QPointF point);
    void block_enter_side(int side);
    void set_spawnZone();
    void add_walls(QGraphicsScene * scene);
    vector<Ground> tile_list;
    //spawn zone
    SpawnZone * spawnZone;
    void add_ground(QGraphicsScene *scene);
    float ground_x, ground_y;
    float ground_height;
    float ground_width;
    float x, y;
    float height;
    float width;
private:
    QPolygonF room;
    int enter_side[4] = {0,0,0,0};

    //define the type of room
    std::string type;
};

#endif // ROOM_H
