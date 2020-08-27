#include "Player.h"
#include "Wall.h"
#include "Game.h"


#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

extern Game * game;

Player::Player(double fps){
    //set value
    speed = 5;

    //shape player
    QImage img(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f0_resize.png");
    setPixmap(QPixmap::fromImage(img));

    weapon = new Weapon();

    // get size image of caracter
    xSize_player = img.width();
    ySize_player = img.height();

    //setTransformOriginPoint(xCoordOrigin,yCoordOrigin);
    //set collider
    colliderBottom = new Collider(2, 2);
    colliderBottom->setPos(this->pos().x() + xSize_player - 5, this->pos().y());
    colliderTop = new Collider(2, 2);
    colliderTop->setPos(this->pos().x() + xSize_player - 5, this->pos().y() + ySize_player - 5);
    colliderLeft = new Collider(2, 2);
    colliderLeft->setPos(this->pos().x() + xSize_player-5, this->pos().y() + ySize_player-5);
    colliderRight = new Collider(2, 2);
    colliderRight->setPos(this->pos().x(), this->pos().y() + ySize_player-5);

    //
    xCoordOrigin = xSize_player / 2;
    yCoordOrigin = ySize_player / 2;

    //
    xSize_Collider = colliderBottom->rect().width();
    ySize_Collider = colliderBottom->rect().height();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()){
        keysPressed_.insert(event->key());
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()){
        keysPressed_.erase(event->key());
    }
}

QPointF Player::getOrigin(){
    return mapToScene(this->pos().x() + xCoordOrigin, this->pos().y() + yCoordOrigin);
}

void Player::set_angle(double argAngle)
{
    angle = argAngle;
}

double Player::get_angle()
{
    return angle;
}


//fonction to move the player
void Player::moving()
{
    int xDisplacement = 0, yDisplacement = 0, xSign = 0, ySign = 0;

    bool zPressed = keysPressed_.count(Qt::Key_Z);
    bool sPressed = keysPressed_.count(Qt::Key_S);
    bool qPressed = keysPressed_.count(Qt::Key_Q);
    bool dPressed = keysPressed_.count(Qt::Key_D);

    if( zPressed || sPressed || qPressed || dPressed){
        if (qPressed){
            xDisplacement += -speed;
            yDisplacement += 0;
        }
        if (dPressed){
            xDisplacement += +speed;
            yDisplacement += 0;
        }
        if (zPressed){
            xDisplacement += 0;
            yDisplacement += -speed;
        }
        if (sPressed){
            xDisplacement += 0;
            yDisplacement += +speed;
        }

        colliderBottom->setPos(pos().x() + xSize_player/2 - xSize_Collider/2, pos().y() +  ySize_player - ySize_Collider + 1 + yDisplacement);
        colliderTop->setPos(pos().x() + xSize_player/2 - xSize_Collider/2, pos().y() + yDisplacement);
        colliderLeft->setPos(pos().x() + xDisplacement,  pos().y() + ySize_player/2 - ySize_Collider/2 );
        colliderRight->setPos(pos().x() + xDisplacement +  xSize_player  - xSize_Collider, pos().y() + ySize_player/2 - ySize_Collider/2);

        QList<QGraphicsItem *> colliding_items_Bottom = colliderBottom->collidingItems();
        QList<QGraphicsItem *> colliding_items_Top = colliderTop->collidingItems();
        QList<QGraphicsItem *> colliding_items_Left = colliderLeft->collidingItems();
        QList<QGraphicsItem *> colliding_items_Right = colliderRight->collidingItems();

        bool verifBottom =  colliderVerif(colliding_items_Bottom);
        bool verifTop = colliderVerif(colliding_items_Top);
        bool verifLeft = colliderVerif(colliding_items_Left);
        bool verifRight = colliderVerif(colliding_items_Right);

        if(!(verifBottom || verifTop || verifLeft || verifRight)){
            if(verifBottom == false && sPressed){
                setPos(x(),y()+speed);
            }
            if (verifTop == false && zPressed){
                setPos(x(),y()-speed);
            }
            if (verifLeft == false && qPressed){
                setPos(x()-speed,y());
            }
            if(verifRight == false && dPressed){
                setPos(x()+speed,y());
            }
        }
        else {
            if(verifBottom && sPressed){
                xSign += 0;
                ySign += -1;

            }
        }
    }

    game->centerOn(this);
    //colliderBottom->setPos(pos().x(), pos().y() +ySize_player);
    //rappel : setPos(x(),y()+speed);
}

bool Player::colliderVerif(QList<QGraphicsItem *> listCollider)
{
    bool verif = false;
    for (int i = 0, n = listCollider.size(); i < n; ++i){
         if (typeid(*(listCollider[i])) == typeid(Wall)){
            verif = true;
            break;
         }
    }
    return verif;
}

void Player::moveCloseToWall()
{

}





