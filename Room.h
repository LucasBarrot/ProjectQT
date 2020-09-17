#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QGraphicsPolygonItem>


class Room : public QObject, public QGraphicsPolygonItem{
    Q_OBJECT
public:
    explicit Room(int x,int y, int width, int height);
    QPointF middle_top_point();
    QPointF middle_left_point();
    QPointF middle_bottom_point();
    QPointF middle_right_point();
    int which_enter(QPointF point);
    int * get_enter_sides();
    void block_enter_side(QPointF point_side);
    QPolygonF get_room();

private:
    QPolygonF room;
    float x, y;
    float height;
    float width;
    int enter_side[4] = {0,0,0,0};


};

#endif // ROOM_H
