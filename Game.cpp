#include "Wall.h"
#include "Game.h"
#include "Room.h"
#include "Player.h"
#include "Network.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QObject>
#include <QGraphicsPolygonItem>
#include <QDebug>

Game::Game(QWidget *parent){
    //create a scene
    scene = new QGraphicsScene();
    scene-> setSceneRect(0,0,1200,600); // make scene 800x600 insted of infinite

    //make the newly created scene the scene to visualize
    //(since Game is a QGraphic Widget it can be use to visualize)
    setScene(scene);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(1200,600);

    double room1_x = rand() % 800, room1_y = rand() % 600;
    double room2_x = rand() % 800, room2_y = rand() % 600;
    double room1_height = rand() % 200 + 50, room1_width = rand() % 200 + 50;
    double room2_height = rand() % 200 + 50, room2_width = rand() % 200 + 50;

    Room * room1 = new Room(room1_x,room1_y,room1_height,room1_width);
    Room * room2 = new Room(room2_x,room2_y,room2_height,room2_width);

    Network * net = new Network(room1, room2);

    int NUMBER_OF_ROOMS = 16; // resulat +2

    double room_x = rand() % 800, room_y = rand() % 600;
    double room_height = rand() % 200 + 50, room_width = rand() % 200 + 50;
    Room * room = new Room(room_x,room_y,room_width,room_height);

    //set network in the scene
    for(int i=0; i<NUMBER_OF_ROOMS; i++){
        while (net->intersect(room->get_room())) {

            double room_x = rand() % 800, room_y = rand() % 600;
            double room_height = rand() % 200 + 50, room_width = rand() % 200 + 50;

            room =  new Room(room_x,room_y,room_width,room_height);
        }
       net->connect(room);
    }


    //scene->addPolygon(net->tunnel_complet);
    scene->addItem(net);


    //is the player colliding with anything?

    //create the player
    player = new Player(net);
    player->setRect(0,0,5,5); //change the rect from 0x0 to def
    player->setPos(750,400);

    //make player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //add player to the scene
    scene->addItem(player);



    show();
}



