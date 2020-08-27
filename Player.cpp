#include "Wall.h"
#include "Player.h"
#include "Bullet.h"
#include "Room.h"
#include "Network.h"
#include <QGraphicsScene>
#include <QDebug>

Player::Player(Network * region) : QObject(){

    // initialize previous pos
    x_prev = pos().x();
    y_prev = pos().y();
    playable_region = region;

}

void Player::keyPressEvent(QKeyEvent * event){

    x_prev = pos().x();
    y_prev = pos().y();

    if(event->key()==Qt::Key_Left)
            setPos(x()-10, y()); 



    else if(event->key()==Qt::Key_Right)
            setPos(x()+10, y());


    else if(event->key()==Qt::Key_Up)
            setPos(x(), y()-10);


    else if(event->key()==Qt::Key_Down)
            setPos(x(), y()+10);



    if (playable_region->contains(pos()) == false)
        setPos(x_prev,y_prev);


}

void Player::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::RightButton or event->button() == Qt::LeftButton )
       {
           qDebug()<<"press";
           //create a bullet
           Bullet * bullet = new Bullet();
           QLineF bullet_vector = QLineF(x(),y(),event->x(), event->y());
           float dx = bullet_vector.dx();
           float dy = bullet_vector.dy();
           bullet->move(dx,dy);
           scene()->addItem(bullet);

       }

}

