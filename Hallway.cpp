#include "Hallway.h"
#include "Room.h"
#include "Wall.h"
#include <QDebug>
#include "Game.h"

Hallway::Hallway(QPolygonF tunnel, int enter_side, QRectF tun1 ,QRectF tun2, QRectF elbow_square): QPolygonF(tunnel)
{
    side = enter_side;
    elbow = elbow_square;
    //corners = corner_list;

    if (side == 0 or side == 2){
        v_arm = tun1;
        h_arm = tun2;
        if(h_arm.left() < v_arm.center().x()){
          direction = 2;

        }
        if(h_arm.right() > v_arm.center().x()){
           direction = 4;
        }
    }

    if (side == 1 or side == 3){
        v_arm = tun2;
        h_arm = tun1;

        if(v_arm.top() < h_arm.center().y()){
            direction = 1;
        }
        if(v_arm.bottom() > h_arm.center().y()){
            direction = 3;
        }
    }
   // qDebug() << direction;
    //qDebug()<< side;
}

Hallway::Hallway(): QPolygonF(){

}


void Hallway::set_vertical_arm(QGraphicsScene *scene ){
    //setup du bras vertical
    //setup des murs
    for(float y=v_arm.top(); y<v_arm.bottom()-16; y+=16){
        Wall *  wall = new Wall(2);
        scene->addItem(wall);
        wall->setPos( v_arm.left(),y);
        wall = new Wall(2);
        scene->addItem(wall);
        wall->setPos(v_arm.right() - 16,y);
        //setup du ground
        for(float x=v_arm.left()+16; x<v_arm.right()-16; x+=16){
            Ground * tile = new Ground();
            scene->addItem(tile);
            tile->setPos(x,y);
        }
    }
}

void Hallway::set_horizontal_arm(QGraphicsScene *scene ){
    //setup du brashorizontal
    //setup des murs
    for(float x=h_arm.left(); x< h_arm.right()-16; x+=16){
        Wall *  wall = new Wall(1);
        scene->addItem(wall);
        wall->setPos(x,h_arm.top());
        wall = new Wall(1);
        scene->addItem(wall);
        wall->setPos(x,h_arm.bottom()-16);
        //qDebug()<< wall->scenePos();
        //setup du ground
        for(float y=h_arm.top()+16; y<h_arm.bottom()-16; y+=16){
            Ground * tile = new Ground();
            scene->addItem(tile);
            tile->setPos(x,y);
        }
    }
}


void Hallway::set_elbow( QGraphicsScene *scene){

    //setup de du coude
    if( (side==0 and direction==2) or (side==3 and direction==3) ){
        float ytop_limit = elbow.top();
        float ybot_limit = elbow.bottom()-16;
        //setup des murs en angle droit (dans les coins)
        Wall *  wall = new Wall(3);
        scene->addItem(wall);
        wall->setPos(elbow.topRight() + QPointF(-16,0));
        wall = new Wall(3);
        scene->addItem(wall);
        wall->setPos(elbow.bottomLeft() + QPointF(0,-16));

        for(float y = elbow.top()+16; y<ybot_limit;y+=16 ){
            Wall * wall = new Wall(2);
            scene->addItem(wall);
            wall->setPos(y,elbow.right()-16);
        }

        //setup des autres murs
        for(float x=elbow.left(); x< elbow.right()-16-16; x+=16){
            Wall * wall = new Wall(1);
            scene->addItem(wall);
            wall->setPos(x,ytop_limit);

            for(float y=ytop_limit+16; y<ybot_limit-16; y+=16){
                if(x!=elbow.left() and y!=ybot_limit ){
                    Ground * tile = new Ground();
                    scene->addItem(tile);
                    tile->setPos(x,y);
                }
             }
        }

    }
///////////////////////////FAIT//////////////////////////////////////////////
    if( (side==0 and direction==4) or (side==1 and direction==3) ){
        //setup des murs en angle droit (dans les coins)
        Wall *  wall = new Wall(4);
        scene->addItem(wall);
        wall->setPos(elbow.topLeft());

        wall = new Wall(4);
        scene->addItem(wall);
        wall->setPos(elbow.bottomRight() + QPointF(-16,-16));

        for(float y = elbow.top()+16; y<elbow.bottom(); y+=16 ){
            Wall * wall = new Wall(2);
            scene->addItem(wall);
            wall->setPos(elbow.left(),y);
        }

        //setup des autres murs
        for(float x=elbow.right()-16; x> elbow.left(); x-=16){
            Wall * wall = new Wall(1);
            scene->addItem(wall);
            wall->setPos(x,elbow.top());

            for(float y=elbow.top()+16; y<=elbow.bottom()-16; y+=16){
                if(QPointF(x,y)==elbow.bottomRight()+QPointF(-16,-16))
                    continue;
                else{
                    Ground * tile = new Ground();
                    scene->addItem(tile);
                    tile->setPos(x,y);}
             }

        }

    }

///////////////////////////FAIT//////////////////////////////////////////////
    if( (side==1 and direction==1) or (side==2 and direction==4) ){
        //setup des murs en angle droit (dans les coins)
        Wall *  wall = new Wall(6);
        scene->addItem(wall);
        wall->setPos(elbow.bottomLeft() + QPointF(0,-16));
        wall = new Wall(6);
        scene->addItem(wall);
        wall->setPos(elbow.topRight() + QPointF(-16,0));

        for(float y = elbow.top(); y<=elbow.bottom()-16-16;y+=16 ){
            Wall * wall = new Wall(2);
            scene->addItem(wall);
            wall->setPos(elbow.left(), y);
        }

        //setup des autres murs
        for(float x=elbow.right()-16; x> elbow.left(); x-=16){
            Wall * wall = new Wall(1);
            scene->addItem(wall);
            wall->setPos(x,elbow.bottom()-16);

            for(float y=elbow.top(); y<=elbow.bottom()-16-16; y+=16){
                if(QPointF(x,y)==elbow.topRight()+QPointF(-16,0))
                    continue;
                else{
                    Ground * tile = new Ground();
                    scene->addItem(tile);
                    tile->setPos(x,y);}
            }
        }
    }

///////////////////////////FAIT//////////////////////////////////////////////
    if( (side==2 and direction==2) or (side==3 and direction==1) ){
        //setup des murs en angle droit (dans les coins)
        Wall *  wall = new Wall(5);
        scene->addItem(wall);
        wall->setPos(elbow.topLeft());
        wall = new Wall(5);
        scene->addItem(wall);
        wall->setPos(elbow.bottomRight() + QPointF(-16,-16));

        for(float y = elbow.top(); y<=elbow.bottom()-16-16;y+=16 ){
            Wall * wall = new Wall(2);
            scene->addItem(wall);
            wall->setPos(elbow.right()-16, y);
        }
        //setup des autres murs
        for(float x=elbow.left(); x<elbow.right()-16; x+=16){
            Wall * wall = new Wall(1);
            scene->addItem(wall);
            wall->setPos(x,elbow.bottom()-16);

            for(float y=elbow.top(); y<=elbow.bottom()-16-16; y+=16){
                if(QPointF(x,y)==elbow.topLeft())
                    continue;
                else{
                    Ground * tile = new Ground();
                    scene->addItem(tile);
                    tile->setPos(x,y);}
            }
        }
    }


}


