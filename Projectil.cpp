#include "Projectil.h"
#include "Game.h"

#include <qmath.h> // qSin, qCos, qTan
#include <QGraphicsScene>
#include <QTime>
#include <QDebug>

extern Game * game;

Projectil::Projectil(double argAngle, double argXPos, double argYPos, double argDamage, QString argPhathImageProjectil){
    //set bullet angle
    angle = argAngle;

    //damage per bullet
    damage = argDamage;

    //load image of the bulllet
    QImage img(argPhathImageProjectil);
    setPixmap(QPixmap::fromImage(img));
    setTransformOriginPoint(img.width()/2, img.height()/2);

    //set the first pos of the bullet
    setPos(argXPos, argYPos);

    //keep that position
    xPosProjectil = argXPos;
    yPosProjectil = argYPos;

    timer = new QTimer;
}

void Projectil::UpdatePosition()
{
    int STEP_SIZE = 150/game->fps;

    double dy = STEP_SIZE * qSin(qDegreesToRadians(angle));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(angle));



    xPosProjectil = x() + dx;
    yPosProjectil = y() + dy;
}

void Projectil::updatePositionOnScreen(int argIndexProjectil)
{
    setPos(xPosProjectil, yPosProjectil);

    QList<QGraphicsItem *> colliding_items = collidingItems();

    //verification that bullet didn't collide with wall or enemy
    bool verifWall = false;
    bool verifCaraterHit = false;
    int indexColliderStop = 0;

    QString nameClassCaracterToHit;
    if((parentName != QString(typeid (Enemy).name()))){
        nameClassCaracterToHit = typeid (Enemy).name();
    }
    else {
        nameClassCaracterToHit = typeid (Player).name();
    }

    //check every colliding block if there are enemy or wall
    for (int indexCollider = 0, n = colliding_items.size(); indexCollider < n; ++indexCollider){
         if (typeid(*(colliding_items[indexCollider])) == typeid(Wall)){
            verifWall = true;
            break;
         }
         else if(typeid (*(colliding_items[indexCollider])).name() == nameClassCaracterToHit){
             verifCaraterHit = true;
             indexColliderStop = indexCollider;
             break;
         }
    }

    //remove item if projectil touch a wall
    if(verifWall){
        game->tabProjectil.removeOne(this);
        scene()->removeItem(this);
        delete this;
    }

    else if(verifCaraterHit){
        //if we shoot enemy (from player)
        if(nameClassCaracterToHit == typeid (Enemy).name()){
            Enemy * enemy = dynamic_cast<Enemy*>(colliding_items.at(indexColliderStop));
            if(game->player->get_playerIsInRoom() == enemy->parentItem()){
                if(enemy->enemyEntity->get_health() - damage > 0){
                    enemy->enemyEntity->set_health(enemy->enemyEntity->get_health() - damage);

                    //remove bullet
                    game->tabProjectil.remove(argIndexProjectil);
                    scene()->removeItem(this);
                    delete this;
                }
                else {
                    //enemy is dead
                    //remove bullet
                    game->tabProjectil.remove(argIndexProjectil);
                    scene()->removeItem(this);
                    delete this;

                    //for a qvector we don't remove it from the scene (if we do it, it going to crash, allocating problem with pointer)
                        delete game->player->get_playerIsInRoom()->tabEnemy.takeAt(game->player->get_playerIsInRoom()->tabEnemy.indexOf(enemy));
                }
            }
        }
        //if it shoot player (from enemy)
        else {

        }
    }
}

void Projectil::set_parentName(QString argParentName){
    parentName = argParentName;
}

QString Projectil::get_parentName(){
    return parentName;
}

QTimer *Projectil::get_timer()
{
    return timer;
}
