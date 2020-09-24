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

    //add to position size of projectil
    // and set the value that keep track of the position
    xPosProjectil = argXPos - img.width()/2;
    yPosProjectil = argYPos - img.height()/2;


    //set the first pos of the bullet
    setPos(xPosProjectil, yPosProjectil);

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
            if(enemy->enemyEntity->get_invulnerability() == false){
                if(enemy->enemyEntity->get_actualHealth() - damage > 0){
                    //enemy take damage
                    enemy->enemyEntity->set_actualHealth(enemy->enemyEntity->get_actualHealth() - damage);

                    //remove bullet
                    game->tabProjectil.remove(argIndexProjectil);
                    scene()->removeItem(this);
                    delete this;
                }
                else {
                    // enemy die

                    SpawnZone * spawnZoneEnemy = dynamic_cast<SpawnZone*>(enemy->parentItem());

                    // add point to player
                    game->addToScore(enemy->get_point());

                    //if boss die spawn a door to new level
                    if(enemy->get_bossOrEnemy()){
                        spawnZoneEnemy->spawnDoorToNextLevel();
                    }

                    //enemy is dead
                    //remove bullet
                    game->tabProjectil.remove(argIndexProjectil);
                    scene()->removeItem(this);
                    delete this;

                    //for a qvector we don't remove it from the scene (if we do it, it going to crash, allocating problem with pointer)
                    delete spawnZoneEnemy->tabEnemy.takeAt(spawnZoneEnemy->tabEnemy.indexOf(enemy));
                }
            }
        }
        //if it shoot player (from enemy)
        else {
            if(game->player->playerEntity->get_invulnerability() == false){
                if(game->player->playerEntity->get_actualHealth() - damage > 0){
                    //player take damage
                    game->player->playerEntity->set_actualHealth(game->player->playerEntity->get_actualHealth() - damage);

                    //remove bullet
                    game->tabProjectil.remove(argIndexProjectil);
                    scene()->removeItem(this);
                    delete this;

                    game->ui->updateHealthUI();
                }
                else {
                    //Player die


                    //remove bullet
                    game->tabProjectil.remove(argIndexProjectil);
                    scene()->removeItem(this);
                    delete this;

                    //close game and open window recap game
                    game->closeGameToRecap();
                }
            }

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

void Projectil::destructionProjectil(){
    delete this;
}
