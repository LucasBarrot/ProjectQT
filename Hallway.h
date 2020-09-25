#ifndef HALLWAY_H
#define HALLWAY_H

#include <QPolygonF>
#include "Room.h"
#include <QVector>
#include <QPointF>
#include <QRectF>


//using namespace std;

class Hallway : public QPolygonF
{
public:
    Hallway(QPolygonF tunnel, int enter_side, QRectF tun1, QRectF tun2, QRectF elbow_square);
    Hallway();
    void set_vertical_arm(QGraphicsScene *scene);
    void set_horizontal_arm(QGraphicsScene *scene);
    void set_elbow(QGraphicsScene *scene);
    QRectF h_arm;
    QRectF v_arm;
    QRectF elbow;

    //vector<QPointF> corners;
    int direction;
    int side;


};

#endif // HALLWAY_H
