#include "Projectil.h"
#include "Game.h"

#include <qmath.h> // qSin, qCos, qTan
#include <QGraphicsScene>
#include <QTime>
#include <QDebug>

extern Game * game;

Projectil::Projectil(double argAngle, double argXPos, double argYPos, double argDamage){
    //set bullet angle
    angle = argAngle;

    //damage per bullet
    damage = argDamage;

    //load image of the bulllet
    QImage img(":/Source/Source/Image/projectil/Projectil_1.png");
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
    int STEP_SIZE = 300/game->fps;

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
    bool verifEnemy = false;
    int indexColliderStop = 0;

    //check every colliding block if there are enemy or wall
    for (int indexCollider = 0, n = colliding_items.size(); indexCollider < n; ++indexCollider){
         if (typeid(*(colliding_items[indexCollider])) == typeid(Wall)){
            verifWall = true;
            break;
         }
         else if(typeid (*(colliding_items[indexCollider])) == typeid (Enemy)){
             verifEnemy = true;
             indexColliderStop = indexCollider;
             break;
         }
    }

    if(verifWall){
        game->tabProjectil.removeOne(this);
        scene()->removeItem(this);
        delete this;
    }
    else if(verifEnemy){
        Enemy * enemy = dynamic_cast<Enemy*>(colliding_items.at(indexColliderStop));
        bool verifBreak = false;
        int indexRoomStop = 0;
        int indexEnemy = 0;
        if(game->player->get_playerIsInRoom() == enemy->parentItem()){
            for(int indexRoom = 0; indexRoom < game->world->tabRoom.size(); ++indexRoom){
                if(game->world->tabRoom.at(indexRoom)->spawnZone == enemy->parentItem()){
                    indexEnemy = game->world->tabRoom.at(indexRoom)->spawnZone->tabEnemy.indexOf(enemy);
                    indexRoomStop = indexRoom;
                    verifBreak = true;
                    break;
                }
            }

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

                //for a q vector we don't remove it from the scene (if we do it, it going to crash, allocating problem with pointer)
                delete enemy;
                game->player->get_playerIsInRoom()->tabEnemy.remove(game->player->get_playerIsInRoom()->tabEnemy.indexOf(enemy));

            }
        }
    }
}

QTimer *Projectil::get_timer()
{
    return timer;
}
