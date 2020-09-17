#ifndef TUNNEL_H
#define TUNNEL_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include "Room.h"
#include <vector>

class Network : public QObject , public QGraphicsPolygonItem{
    Q_OBJECT
public:
    Network(Room * room1, Room * room2);
    QPolygonF get_poly();
    void add_room_to_memory(Room * room);
    void connect(Room *room);
    bool intersect(QPolygonF);
    QPolygonF build_hallway(QPointF point1, QPointF point2, int enter_side);
private:
    QPolygonF network;
    QList<Room *> rooms_in_net; //contient les chambre avec leurs coordonnées

signals:

};

#endif // TUNNEL_H
