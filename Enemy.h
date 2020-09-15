#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QLineF>
#include <QObject>
#include <QTimer>

#include "EntityCaracter.h"
#include "Projectil.h"

class Enemy : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Enemy();

    //update Enemy
    void UpdateEnemy();

    //update sprite enemy
    void UpdateSpriteEnemy();

    //prevPos
    void set_prevPos(QPointF argPrevPos);

    //set status to attack mode
    void set_ToAttackMode();

    //set object in the scene (enemyEntity and collider)
    void set_objectOfEnemyInScene();

    //set entity enemy
    Entity * enemyEntity;

    //set a collider to detect they are obstacle to shoot player
    QGraphicsRectItem * lineOfSight;


private:
    //set a entity necromancer
    Entity * set_necromancer();

    //path image projectil shooted by enemy
    QString pathImageProjectil;

    //minimal distance to player of the enemy
    double distanceMinamalToPlayer;

    //shoot
    //shoot function
    void shootSimple(double angle);
    //update variable shootSimpleReady
    void updateShootSimple();
    //variable to check if shoot is ready
    bool shootSimpleReady;

    //move enemy
    void moveEnemy(double argAngle);

    //prev position of enemy (if it touch a wall or object reset position)
    double prevXPos;
    double prevYPos;

};

#endif // ENEMY_H
