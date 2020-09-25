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
    Enemy(int argIndex, bool argBossOrEnemy);

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

    //get boos or enemy
    bool get_bossOrEnemy();

    //set and get point
    void set_point(int argPoint);
    int get_point();

    //set and get rate of fire
    void set_rateFire(double argNbShootPerSecond);
    double get_rateFire();

    //set and get damage
    void set_damage(double argDamage);
    double get_damage();

    //set speedProjectil
    void set_speedProjectil(double argSpeed);

    //set entity enemy
    EntityCaracter * enemyEntity;

    //set a collider to detect they are obstacle to shoot player
    QGraphicsRectItem * lineOfSight;

    //set path projectil
    void set_pathProjectil(QString argPath);

    //destuction enemy
    void destructionEnemy();

    //set and get attack enemy
    void set_attack(void (Enemy::*ptr)(double arg_1));
    void doAttack(double arg_1);

    //list attack enemy
    //shoot function
    //simple shoot
    void shootSimple(double argAngle);

    //triple shoot
    void multipleSimpleShoot(double argAnglee);

    //set parameter
    void set_angleConeAttack(double argAngleCone);
    void set_nbShootAttack(int argAngleCone);

private:
    //index in list enemy for creation of entity
    int indexListEnemy;

    //rate of fire enemy
    double rateFire;

    //damage
    double damage;

    //number of point get from enemy
    int point;

    //speed projectil
    double speedProjectil;

    //verif if the Enemy is a boss or a simple enemy
    //boss: true
    //enemy: false
    bool bossOrEnemy;

    //path image projectil shooted by enemy
    QString pathImageProjectil;

    //minimal distance to player of the enemy
    double distanceMinamalToPlayer;

    //shoot
    //update variable shootSimpleReady
    void updateShootSimple();
    //variable to check if shoot is ready
    bool shootSimpleReady;

    //move enemy
    void moveEnemy(double argAngle);

    //prev position of enemy (if it touch a wall or object reset position)
    double prevXPos;
    double prevYPos;

    //entity Enemy set
    bool initializedEntityEnemy;

    //set attack of enemy
    void (Enemy::*attack)(double arg);

    //parameter attack
    double angleConeAttack;
    int nbShootAttack;

};

#endif // ENEMY_H
