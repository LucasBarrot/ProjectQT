#include "Network.h"
#include "math.h"
#include "Room.h"
#include <QPointF>
#include <QLineF>
#include <QDebug>
#include <QMargins>
#include <QTransform>
#include <vector>

using namespace std;


Network::Network(Room * room1, Room * room2) : QObject(), QGraphicsPolygonItem()
{
    //listes des entrées potentielles des rooms
    QList<QPointF> r1_points, r2_points;
    //liste des entrées free/ non-free
    int * enter_side_r1 = room1->get_enter_sides();
    int * enter_side_r2 = room2->get_enter_sides();
    // recherche des entrées pas encore utilisé par le réseau
    if (enter_side_r1[0]==0)
        r1_points.append(room1->middle_top_point());
    if (enter_side_r1[1]==0)
        r1_points.append(room1->middle_left_point());
    if (enter_side_r1[2]==0)
        r1_points.append(room1->middle_bottom_point());
    if (enter_side_r1[3]==0)
        r1_points.append(room1->middle_right_point());

    if (enter_side_r2[0]==0)
        r2_points.append(room2->middle_top_point());
    if (enter_side_r2[1]==0)
        r2_points.append(room2->middle_left_point());
    if (enter_side_r2[2]==0)
        r2_points.append(room2->middle_bottom_point());
    if (enter_side_r2[3]==0)
        r2_points.append(room2->middle_right_point());

    QPointF tunnel_point1, tunnel_point2, center;
    double d_prev = sqrt(pow((r1_points[0].x()-r2_points[0].x()),2) + pow((r1_points[0].y()-r2_points[0].y()),2));
    for (QPointF point1 : r1_points){
        for (QPointF point2 : r2_points){
            double d = sqrt(pow(point1.x()-point2.x(),2) + pow(point1.y()-point2.y(),2));
            if(d_prev >= d){
                tunnel_point1 = point1; // point1 du tunnel partant de la room1
                tunnel_point2 = point2; // point2 du tunnel partant de la room2

                center = QPointF((point1.x()+point2.x())/2, (point1.y()+point2.y())/2);
                d_prev = d;
            }
        }
    }
    room1->block_enter_side(tunnel_point1);  // enregistre les entrées bloquées
    room2->block_enter_side(tunnel_point2);

    add_room_to_memory(room1); // enregistre les chambres déjà utilisé
    add_room_to_memory(room2);

    QLineF line = QLineF(tunnel_point1, tunnel_point2);

    QTransform t = QTransform().translate(center.x(),center.y()).rotate(-line.angle()-90).translate(-center.x(),-center.y());
    QRectF tun(tunnel_point1.x(),tunnel_point1.y(),50,d_prev+20);

    tun.moveCenter(center);

    QPolygonF tunnel(tun);

    tunnel = t.map(tunnel);

    network = tunnel.united(room1->get_room());
    network = network.united(room2->get_room());


    setPolygon(network);


}



QPolygonF Network::get_poly()
{
    return network;
}



void Network::add_room_to_memory(Room * room){
    rooms_in_net.append(room);
}

void Network::connect(Room * new_room){
    //liste des entrées free/ non-free du network
    vector<QList<QPointF>> network_points;
    // recherche des entrées pas encore utilisé par le réseau
    for (Room * room : rooms_in_net ){
        //listes des entrées potentielles des rooms
        QList<QPointF> entries_room;
        int * enter_sides = room->get_enter_sides();
        if (enter_sides[0]==0)
            entries_room.append(room->middle_top_point());
        if (enter_sides[1]==0)
            entries_room.append(room->middle_left_point());
        if (enter_sides[2]==0)
            entries_room.append(room->middle_bottom_point());
        if (enter_sides[3]==0)
           entries_room.append(room->middle_right_point());

        network_points.push_back(entries_room);
     }

    //listes des entrées potentielles des rooms
    QList<QPointF> new_room_points;
    //liste des entrées free/ non-free de la nouvelle salle
    int * entries_new_room = new_room->get_enter_sides();

    if (entries_new_room[0]==0)
        new_room_points.append(new_room->middle_top_point());
    if (entries_new_room[1]==0)
        new_room_points.append(new_room->middle_left_point());
    if (entries_new_room[2]==0)
        new_room_points.append(new_room->middle_bottom_point());
    if (entries_new_room[3]==0)
        new_room_points.append(new_room->middle_right_point());


    QPointF tunnel_point1, tunnel_point2 ;
    double d_prev = sqrt(pow((network_points[0][0].x()-new_room_points[0].x()),2) + pow((network_points[0][0].y()-new_room_points[0].y()),2));
    for (QList<QPointF> list_point1 : network_points)
    {
         for (QPointF point1 : list_point1)
         {
             for (QPointF point2 : new_room_points)
             {
                 double d = sqrt(pow(point1.x()-point2.x(),2) + pow(point1.y()-point2.y(),2));
                 if(d_prev >= d)
                 {
                     tunnel_point1 = point1; // point1 du tunnel partant de la salle appartenant au réseau
                     tunnel_point2 = point2; // point2 du tunnel partant de la new room
                     d_prev = d;

                 }
             }
         }
     }
    QPointF center = QPointF((tunnel_point1.x()+tunnel_point2.x())/2, (tunnel_point1.y()+tunnel_point2.y())/2);

    for (Room * room : rooms_in_net){ //TODO: mettre une condition dans cette boucle pour ne pas se parcourir tout le réseau
        // parcours les salles du réseau pour bloqué l'entréesélectionnée
        room->block_enter_side(tunnel_point1);
     }
    new_room->block_enter_side(tunnel_point2);

    add_room_to_memory(new_room); // enregistre la nouvelle chambre dans le réseau

    QLineF line = QLineF(tunnel_point1, tunnel_point2);

    QTransform t = QTransform().translate(center.x(),center.y()).rotate(-line.angle()-90).translate(-center.x(),-center.y());
    QRectF tun(tunnel_point1.x(),tunnel_point1.y(),50,d_prev+20);
    tun.moveCenter(center);

    QPolygonF tunnel(tun);

    tunnel = t.map(tunnel);


    network = network.united(tunnel);
    network = network.united(new_room->get_room());

    setPolygon(network);

}

bool Network::intersect(QPolygonF room){
 if ( network.intersects(room) )
     return true;
 else
     return false;
}


