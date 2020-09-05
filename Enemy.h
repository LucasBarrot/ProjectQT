#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>

#include "Entity.h"

class Enemy : public QGraphicsRectItem {
public:
    Enemy();

    //update Enemy
    void UpdateEnemy();

    //prevPos
    void set_prevPos(QPointF argPrevPos);

    //set status to attack mode
    void set_ToAttackMode();

    //set object in the scene (enemyEntity and collider)
    void set_objectOfEnemyInScene();

    //set entity enemy
    Entity * enemyEntity;



private:
    //set a entity necromancer
    Entity * set_necromancer();

    //minimal distance to player of the enemy
    double distanceMinamalToPlayer;

    //move enemy
    void moveEnemy(double argAngle);

    //prev position of enemy (if it touch a wall or object reset position)
    double prevXPos;
    double prevYPos;
};

#endif // ENEMY_H
