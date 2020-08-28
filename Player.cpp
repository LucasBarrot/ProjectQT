#include "Player.h"
#include "Wall.h"
#include "Game.h"

#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <math.h>

extern Game * game;

Player::Player(double fps){
    //set value
    speed = 150 / fps;

    //shape player
    QImage img(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f0.png");

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

    //set status (test)
    status = 0;

    //set index sprite
    indexSprite = 0;

    //set Sprite
    spriteIdle.append(addSprite(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f0.png"));
    spriteIdle.append(addSprite(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f1.png"));
    spriteIdle.append(addSprite(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f2.png"));
    spriteIdle.append(addSprite(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f3.png"));

    //set Current Sprite
    currentSprite = addSprite(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f0.png");

    //spriteHit.
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

void Player::updateSprite()
{
    double xPrev = x();
    double yPrev = y();

    currentSprite = spriteIdle.at(indexSprite);

    if(verifMirroredSprite == true){
        QPixmap mirrored = currentSprite->transformed(QTransform().scale(-1,1));
        setPixmap(mirrored);
    }
    else {
        setPixmap(*currentSprite);
    }

    if(indexSprite == 0){
        setPos(xPrev ,yPrev + spriteIdle.at(spriteIdle.size() - 1)->height() - spriteIdle.at(indexSprite)->height());
    }
    else {
        setPos(xPrev ,yPrev + spriteIdle.at(indexSprite - 1)->height() - spriteIdle.at(indexSprite)->height());
    }

    indexSprite ++;
    if(indexSprite > spriteIdle.size() - 1){
        indexSprite = 0;
        //verifMirroredSprite = false;
    }
}

QPixmap Player::get_currentSprite()
{
    return *currentSprite;
}

QPixmap * Player::addSprite(std::string pathFile)
{
    QPixmap * pixmap = new QPixmap();
    pixmap->load(QString::fromStdString(pathFile));
    return pixmap;
}


//fonction to move the player
void Player::moving()
{
    int xDisplacement = 0, yDisplacement = 0, xSign = 0, ySign = 0;
    bool verifLeft = false, verifRight = false, verifTop = false, verifBottom = false;

    bool zPressed = keysPressed_.count(Qt::Key_Z);
    bool sPressed = keysPressed_.count(Qt::Key_S);
    bool qPressed = keysPressed_.count(Qt::Key_Q);
    bool dPressed = keysPressed_.count(Qt::Key_D);

    if( zPressed || sPressed || qPressed || dPressed){
        if(!(qPressed && dPressed) && (qPressed || dPressed)){
            if (qPressed){
                xDisplacement += -speed;
                yDisplacement += 0;
            }
            if (dPressed){
                xDisplacement += +speed;
                yDisplacement += 0;
            }

            colliderLeft->setPos(pos().x() + xDisplacement + xSize_Collider,  pos().y() + ySize_player/2 - ySize_Collider/2 );
            colliderRight->setPos(pos().x() + xDisplacement +  xSize_player  - xSize_Collider, pos().y() + ySize_player/2 - ySize_Collider/2);

            QList<QGraphicsItem *> colliding_items_Left = colliderLeft->collidingItems();
            QList<QGraphicsItem *> colliding_items_Right = colliderRight->collidingItems();

            verifLeft = colliderVerif(colliding_items_Left);
            verifRight = colliderVerif(colliding_items_Right);
        }
        if(!(zPressed && sPressed) && (zPressed || sPressed)){
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

            QList<QGraphicsItem *> colliding_items_Bottom = colliderBottom->collidingItems();
            QList<QGraphicsItem *> colliding_items_Top = colliderTop->collidingItems();

            verifBottom =  colliderVerif(colliding_items_Bottom);
            verifTop = colliderVerif(colliding_items_Top);
        }

        if(keysPressed_.size() == 1){
            if(verifBottom == false && sPressed){
                setPos(x(),y()+speed);
            }
            else if (verifTop == false && zPressed){
                setPos(x(),y()-speed);
            }
            else if (verifLeft == false && qPressed){
                setPos(x()-speed,y());
            }
            else if(verifRight == false && dPressed){
                setPos(x()+speed,y());
            }
        }
        else {

            if(verifBottom == false && sPressed && verifRight == false && dPressed){
                setPos(x() + int(speed / sqrt(2)), y() + int(speed / sqrt(2)));
                qDebug() <<  + (speed / sqrt(2)) <<  + (speed / sqrt(2));
            }
            else if (verifTop == false && zPressed && verifLeft == false && qPressed ){
                setPos(x() - int(speed / sqrt(2)),y() - int(speed / sqrt(2)));
            }
            else if (verifRight == false && dPressed && verifTop == false && zPressed){
                setPos(x() + int(speed / sqrt(2)),y() - int(speed / sqrt(2)));
            }
            else if(verifLeft == false && qPressed && verifBottom == false && sPressed){
                setPos(x() - int(speed / sqrt(2)),y() + int(speed / sqrt(2)));
            }
        }

        if(verifBottom || verifTop || verifLeft || verifRight) {
            if(sPressed){
                xSign = 0;
                ySign = 1;
                moveCloseToWall(xSign, ySign, colliderBottom);
            }
            if(zPressed){
                xSign = 0;
                ySign = -1;
                moveCloseToWall(xSign, ySign, colliderTop);
            }
            if(qPressed){
                xSign = -1;
                ySign = 0;
                moveCloseToWall(xSign, ySign, colliderLeft);
            }
            if(dPressed){
                xSign = 1;
                ySign = 0;
                moveCloseToWall(xSign, ySign, colliderRight);
            }
        }
    }

    game->centerOn(x() + xCoordOrigin, y() + currentSprite->height()  + yCoordOrigin);
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

void Player::moveCloseToWall(int xSign, int ySign, Collider * collider)
{
    int xDisplacement = 0, yDisplacement = 0;
    for(int indexSpeed = 0; indexSpeed < speed; indexSpeed++){
        if(collider == colliderTop or collider == colliderBottom){
            colliderBottom->setPos(pos().x() + xSize_player/2 - xSize_Collider/2, pos().y() +  ySize_player - ySize_Collider + yDisplacement);
            colliderTop->setPos(pos().x() + xSize_player/2 - xSize_Collider/2, pos().y() + yDisplacement);
        }
        else {
            colliderLeft->setPos(pos().x() + xDisplacement  + xSize_Collider,  pos().y() + ySize_player/2 - ySize_Collider/2 );
            colliderRight->setPos(pos().x() + xDisplacement +  xSize_player  - xSize_Collider - xSize_Collider, pos().y() + ySize_player/2 - ySize_Collider/2);
        }

        QList<QGraphicsItem *> colliding_items= collider->collidingItems();

        bool verif =  colliderVerif(colliding_items);

        if(verif){
            break;
        }

        xDisplacement += xSign;
        yDisplacement += ySign;
    }

    setPos(x() + xDisplacement, y() + yDisplacement);
}





