#include "World.h"
#include "Room.h"

#include <stdlib.h>
#include <QDebug>
#include <random>
#include <time.h>
#include <math.h>
#include <QPointF>
#include <vector>
#include <array>
#include "Hallway.h"

using namespace std;


World::World(Room * room1, Room * room2) : QObject(), QGraphicsPolygonItem(){
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
    int enter_side = room1->which_enter(tunnel_point1);
    room1->block_enter_of_this_point(tunnel_point1);  // enregistre les entrées bloquées
    room2->block_enter_of_this_point(tunnel_point2);

    add_room_to_memory(room1); // enregistre les chambres déjà utilisé
    add_room_to_memory(room2);
    //Hallway little_tunnel_complete;
    //QRectF tun1;
    //QRectF tun2;
    Hallway tunnel_complete = build_hallway(tunnel_point1, tunnel_point2, enter_side);

    //rect_h.push_back(tun1);
    //rect_v.push_back(tun2);
    /*
    qDebug() <<"size : "<< tunnel_complete.size();
    for (int i =0; i< tunnel_complete.size();i++){
        qDebug() <<"idx : "<< tunnel_complete[i];

    }
    qDebug()<< "enter_side :" <<enter_side;

    if (enter_side==0){
    qDebug()<< "position 1 or 6 :" << tun2.x() << "  "<< tun2.y();
    }

    if (enter_side==1){
    qDebug()<< "position 6 :" << tun2.x() << "  "<< tun2.y();
    }

    if (enter_side==2){
    qDebug()<< "position 2 :" << tun2.x() << "  "<< tun2.y();
    }

    if (enter_side==3){
    qDebug()<< "position 1 or 6 :" << tun2.x() << "  "<< tun2.y()+tun2.height();
    }
    */
    hallways_list.push_back({tunnel_complete});
    network = tunnel_complete.united(* room1);
    network = network.united(* room2);


    setPolygon(network);
}

QPolygonF World::get_poly()
{
    return network;
}



void World::add_room_to_memory(Room * room){
    rooms_in_net.append(room);
}

void World::connect(Room * new_room){
    //liste des entrées free/ non-free du network
    vector<QList<QPointF>> network_points = get_network_free_points();

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


    int room_number = 0;
    vector<array<float, 6>> rooms_and_distances;
    for (QList<QPointF> list_point1 : network_points)
    {
         for (QPointF point1 : list_point1)
         {
             for (QPointF point2 : new_room_points)
             {
                 float d = sqrt(pow(point1.x()-point2.x(),2) + pow(point1.y()-point2.y(),2));
                 rooms_and_distances.push_back( array<float, 6>{d,(float)room_number, (float)point2.x(), (float)point2.y(), (float)point1.x(), (float)point1.y()}); 
             }
         }
         room_number++;
     }
    sort(rooms_and_distances.begin(), rooms_and_distances.end());
    QPointF enter_point_new_room;
    Hallway tunnel_complete;
    QPolygonF translated_tun;
    //QRectF tun1, tun2;
    int enter_side;
    int i=0;
    do{
        room_number = rooms_and_distances[i][1];
        enter_point_new_room = QPointF(rooms_and_distances[i][2], rooms_and_distances[i][3]);
        QPointF enter_point_net_room(rooms_and_distances[i][4], rooms_and_distances[i][5]);
        enter_side = rooms_in_net[room_number]->which_enter(enter_point_net_room);

        tunnel_complete = build_hallway(enter_point_net_room, enter_point_new_room, enter_side);
        if(enter_side==0)
            translated_tun = tunnel_complete.translated(0,-1);
        if(enter_side==1)
            translated_tun = tunnel_complete.translated(-1,0);
        if(enter_side==2)
            translated_tun = tunnel_complete.translated(0,+1);
        if(enter_side==3)
            translated_tun = tunnel_complete.translated(+1,0);
        i++;

    }while(network.intersects(translated_tun));

    rooms_in_net[room_number]->block_enter_side(enter_side);

    new_room->block_enter_of_this_point(enter_point_new_room);
    hallways_list.push_back({tunnel_complete});


    //rect_h.push_back(tun1);
   // rect_v.push_back(tun2);

    /*
    qDebug() <<"size : "<< tunnel_complete.size();
    for (int i =0; i< tunnel_complete.size();i++){
        qDebug() <<"idx : "<< tunnel_complete[i];

    }
    qDebug()<< "enter_side :" <<enter_side;
    if (enter_side==0){
    qDebug()<< "tun2 xy:" << tun2.x() << "  "<< tun2.y();
    }

    if (enter_side==1){
    qDebug()<< "tun2 xy :" << tun2.x() << "  "<< tun2.y();
    }

    if (enter_side==2){
    qDebug()<< "tun2 xy :" << tun2.x() << "  "<< tun2.y();
    }

    if (enter_side==3){
    qDebug()<< "tun2 xy :" << tun2.x() << "  "<< tun2.y();
    }
    */
    add_room_to_memory(new_room); // enregistre la nouvelle chambre dans le réseau

    network = network.united(tunnel_complete);
    network = network.united(* new_room);

    setPolygon(network);

}


bool World::intersect(QPolygonF room){
 if ( network.intersects(room) )
     return true;
 else
     return false;
}

vector<QList<QPointF> > World::get_network_free_points()
{    // recherche des entrées pas encore utilisé par le réseau
    vector<QList<QPointF>> network_points;

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
        //récupère les coordonnées d'entré de chaque chambre du réseau
        network_points.push_back(entries_room);
     }
    return network_points;
}

Hallway World::build_hallway(QPointF tunnel_point1, QPointF tunnel_point2, int enter_side )
{
    QRectF tun1, tun2, rect_hall1, rect_hall2, elbow_square;
    //vector<QPointF> corner_list;
    //entrée du haut
    if(enter_side == 0 ){
        QPointF join_point = QPointF(tunnel_point1.x(),tunnel_point2.y());
        tun1 = QRectF( QPointF(join_point.x()-24,join_point.y()-24), QPointF(tunnel_point1.x()+24,tunnel_point1.y()) );
        rect_hall1 = tun1.marginsRemoved(QMarginsF(0, 48,0, 0));
        elbow_square = QRectF(tun1.topLeft(), QPointF(join_point.x()+24, join_point.y()+24));
        if(tunnel_point2.x() < tunnel_point1.x()){
            tun2 = QRectF( QPointF(tunnel_point2.x(),tunnel_point2.y()-24), QPointF(join_point.x()+24,join_point.y()+24));
            rect_hall2 = tun2.marginsRemoved(QMarginsF(0,0,48, 0));
        }
        else{
            tun2 = QRectF( QPointF(join_point.x()-24,join_point.y()-24), QPointF(tunnel_point2.x(),tunnel_point2.y()+24));
            rect_hall2 = tun2.marginsRemoved(QMarginsF(48,0,0, 0));
        }

     }

    //entrée de gauche
    if(enter_side == 1 ){
        QPointF join_point(tunnel_point2.x(),tunnel_point1.y());
        tun1 = QRectF( QPointF(join_point.x()-24,join_point.y()-24), QPointF(tunnel_point1.x(),tunnel_point1.y()+24) );
        rect_hall1 = tun1.marginsRemoved(QMarginsF(48,0,0, 0));
        elbow_square = QRectF(tun1.topLeft(), QPointF(join_point.x()+24, join_point.y()+24));
        if(tunnel_point2.y() < tunnel_point1.y()){
            tun2 = QRectF( QPointF(tunnel_point2.x()-24,tunnel_point2.y()), QPointF(join_point.x()+24,join_point.y()+24) );
            rect_hall2 =  tun2.marginsRemoved(QMarginsF(0,0,0,48));
        }
        else{
            tun2 = QRectF( QPointF(join_point.x()-24, join_point.y()-24), QPointF(tunnel_point2.x()+24,tunnel_point2.y()) );
            rect_hall2 = tun2.marginsRemoved(QMarginsF(0,48,0, 0));
        }

     }

    //entrée du bas
    if(enter_side == 2 ){
        QPointF join_point(tunnel_point1.x(),tunnel_point2.y());
       tun1 = QRectF( QPointF(tunnel_point1.x()-24,tunnel_point1.y()), QPointF(join_point.x()+24,join_point.y()+24) );//
       rect_hall1 = tun1.marginsRemoved(QMarginsF(0,0,0, 48));
       elbow_square = QRectF(QPointF(join_point.x()-24, join_point.y()-24), tun1.bottomRight());
       if(tunnel_point2.x() < tunnel_point1.x()){
            tun2 = QRectF( QPointF(tunnel_point2.x(),tunnel_point2.y()-24), QPointF(join_point.x()+24,join_point.y()+24) );
            rect_hall2 = tun2.marginsRemoved(QMarginsF(0,0,48,0));
       }
       else{
           tun2 = QRectF( QPointF(join_point.x()-24,join_point.y()-24), QPointF(tunnel_point2.x(),tunnel_point2.y()+24) );
           rect_hall2 = tun2.marginsRemoved(QMarginsF(48,0,0,0));
        }

     }

    //entrée de droite
    if(enter_side == 3 ){
        QPointF join_point(tunnel_point2.x(),tunnel_point1.y());
        tun1 = QRectF( QPointF(tunnel_point1.x(),tunnel_point1.y()-24), QPointF(join_point.x()+24,join_point.y()+24) );//
        rect_hall1 = tun1.marginsRemoved(QMarginsF(0, 0, 48, 0));
        elbow_square = QRectF(QPointF(join_point.x()-24, join_point.y()-24), tun1.bottomRight());
        if(tunnel_point2.y() < tunnel_point1.y()){
            tun2 = QRectF( QPointF(tunnel_point2.x()-24,tunnel_point2.y()), QPointF(join_point.x()+24,join_point.y()+24) );
            rect_hall2 = tun2.marginsRemoved(QMarginsF(0, 0, 0, 48));
        }
        else{
            tun2 = QRectF( QPointF(join_point.x()-24,join_point.y()), QPointF(tunnel_point2.x()+24,tunnel_point2.y()) );
            rect_hall2 =  tun2.marginsRemoved(QMarginsF(0, 48, 0, 0));
        }

     }

    QPolygonF tunnel1(tun1), tunnel2(tun2);
    QPolygonF tunnel_complete = tunnel1.united(tunnel2);



    //little_tun1 = tun1.marginsRemoved(QMarginsF(16, 16, 16, 16));
    //little_tun2 = tun2.marginsRemoved(QMarginsF(16, 16, 16, 16));

    //* little_tunnel_complete = QPolygonF(little_tun1).united(QPolygonF(little_tun2));



    //QTransform transf;
    //transf=trans.scale(1.5,1.5);
    //QPolygonF qpf2=trans.map(qpf);    //Hallway tunnel_complete = Hallway(tunnel,tun1, tun2 );

    return Hallway(tunnel_complete, enter_side, rect_hall1, rect_hall2, elbow_square);
}
