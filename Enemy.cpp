#include "Enemy.h"

#include "Game.h"

#include <QGraphicsScene>
#include <qmath.h> // qSin, qCos, qTan
#include <QDebug>
#include <random>

extern Game * game;

Enemy::Enemy(int argIndex, bool argBossOrEnemy){
    //set index list enemy
    indexListEnemy = argIndex;

    //set boss or enemy
    bossOrEnemy = argBossOrEnemy;

    //distance minimal to player
    distanceMinamalToPlayer = 100;

    prevXPos = 0;
    prevYPos = 0;

    shootSimpleReady = true;

    lineOfSight = new QGraphicsRectItem();
    lineOfSight->setParentItem(this);
    lineOfSight->setPen(Qt::NoPen);

    //set to false initialized entity enemy because yet is not set
    initializedEntityEnemy = false;

    //set parameter attack to 0
    angleConeAttack = 0;
    nbShootAttack = 0;
}

void Enemy::UpdateEnemy(){
    if(initializedEntityEnemy == false){
        //now we gonna initialized entity so we can change initializedEntityEnemy
        initializedEntityEnemy = true;

        //set entity necromancer        
        if(bossOrEnemy == false){
            enemyEntity = game->listEnemy->get_constructeurOnTab(indexListEnemy, this);
        }
        else {
            enemyEntity = game->listBoss->get_constructeurOnTab(indexListEnemy, this);

            //setPos in scene
            setPos(parentItem()->boundingRect().width() / 2 - enemyEntity->get_widthEntity() / 2 ,  parentItem()->boundingRect().height() / 2 - enemyEntity->get_heightEntity() /2);
            set_prevPos(pos());
        }

        enemyEntity->setParentItem(this);


        //test
        setRect(0,0, enemyEntity->get_widthEntity(), enemyEntity->get_heightEntity());

        enemyEntity->colliderBottom->setParentItem(this);
        enemyEntity->colliderTop->setParentItem(this);
        enemyEntity->colliderLeft->setParentItem(this);
        enemyEntity->colliderRight->setParentItem(this);
    }
    QPointF pt1(parentItem()->x() + x()  + rect().width()/2, parentItem()->y() + y() + rect().height()/2);
    QPointF pt2(game->player->x() + game->player->playerEntity->get_widthEntity()/2 , game->player->y() + game->player->playerEntity->get_heightEntity()/2);
    QLineF line(pt1,pt2);
    QLineF lineInvert(pt2, pt1);

    //rotate enemy to player
    if(90 < line.angle() && line.angle() < 270 && enemyEntity->get_verifRotation() == false){
        enemyEntity->setPixmap(enemyEntity->get_currentSprite().transformed(QTransform().scale(-1,1)));
        enemyEntity->set_verifRotation(true);
    }
    else if((line.angle() < 90 || 270 < line.angle()) && enemyEntity->get_verifRotation() == true){
        enemyEntity->setPixmap(enemyEntity->get_currentSprite());
        enemyEntity->set_verifRotation(false);
    }

    //add IA Enemy
    //if is in attack mode
    if(enemyEntity->get_status() == 1){
        //move away from player if too close
        if(line.length() < distanceMinamalToPlayer * 0.8){
            moveEnemy(-lineInvert.angle() + (rand()%60 - 30));
        }
        //move closer from player if too far
        else if(line.length() > distanceMinamalToPlayer * 1.2) {
            moveEnemy(-line.angle() + (rand()%60 - 30));
        }
        //stay at the same distance
        else {
            // not finish
            int directionRand = (rand() % 3 ) - 2;
            if(directionRand != 0){
                moveEnemy(-line.angle() + 90 * directionRand );
            }
        }

        //Shoot
        if(shootSimpleReady){
            QImage img = QImage(pathImageProjectil);
            lineOfSight->setRotation(0);
            lineOfSight->setRect(enemyEntity->get_widthEntity()*1.5, enemyEntity->get_heightEntity()/2 - img.height()/2, line.length() - enemyEntity->get_widthEntity() * 1.5, img.height());
            lineOfSight->setTransformOriginPoint(enemyEntity->get_widthEntity()/2, enemyEntity->get_heightEntity()/2);
            lineOfSight->setRotation(-line.angle());

            QList<QGraphicsItem *> colliding_items_ = lineOfSight->collidingItems();

            bool verifLineOFSightClear = !enemyEntity->colliderVerif(colliding_items_, typeid (Wall).name(), typeid (Enemy).name());

            if(verifLineOFSightClear){
                shootSimple(-line.angle());
                doAttack(-line.angle());
                shootSimpleReady = false;
                QTimer::singleShot(rateFire, this, &Enemy::updateShootSimple);

            }
        }
    }
}

void Enemy::UpdateSpriteEnemy(){
        enemyEntity->chooseSprite();
}

void Enemy::set_prevPos(QPointF argPrevPos){
    prevXPos = argPrevPos.x();
    prevYPos = argPrevPos.y();
}

void Enemy::set_ToAttackMode(){
    //set entity to attack mode
    enemyEntity->set_status(1);

    //disable invulnerability
    enemyEntity->set_invulnerability(false);
}

void Enemy::set_objectOfEnemyInScene(){
//    setRect(0,0, enemyEntity->get_widthEntity(), enemyEntity->get_heightEntity());

//    enemyEntity->colliderBottom->setParentItem(this);
//    enemyEntity->colliderTop->setParentItem(this);
//    enemyEntity->colliderLeft->setParentItem(this);
    //    enemyEntity->colliderRight->setParentItem(this);
}

bool Enemy::get_bossOrEnemy(){
    return bossOrEnemy;
}

void Enemy::set_point(int argPoint){
    point = argPoint;
}

int Enemy::get_point(){
    return point;
}

void Enemy::set_rateFire(double argNbShootPerSecond){
    rateFire = 1000/argNbShootPerSecond;
}

double Enemy::get_rateFire(){
    return rateFire;
}

void Enemy::set_damage(double argDamage){
    damage = argDamage;
}

double Enemy::get_damage(){
    return damage;
}

void Enemy::set_pathProjectil(QString argPath){
    pathImageProjectil = argPath;
}

void Enemy::destructionEnemy(){
    delete this;
}

void Enemy::set_attack(void (Enemy::*ptr)(double argAngle)){
    attack = ptr;
}

void Enemy::doAttack(double arg_1){
    (this->*attack)(arg_1);
}

void Enemy::updateShootSimple()
{
    shootSimpleReady = true;
}

void Enemy::moveEnemy(double argAngle){
    double dx =  enemyEntity->get_displacement() * qCos(qDegreesToRadians(argAngle));
    double dy =  enemyEntity->get_displacement() * qSin(qDegreesToRadians(argAngle));

    double posDx = pos().x() + dx;
    double posDy = pos().y() + dy;

    //collider enemy
    //set variable
    bool verifLeft = false, verifRight = false, verifTop = false, verifBottom = false;

    //move colllider to the new position of enemy
    enemyEntity->colliderLeft->setPos(enemyEntity->colliderLeft->x(), enemyEntity->colliderLeft->y());
    enemyEntity->colliderRight->setPos(enemyEntity->colliderRight->x(), enemyEntity->colliderRight->y());
    enemyEntity->colliderBottom->setPos(enemyEntity->colliderBottom->x(), enemyEntity->colliderBottom->y());
    enemyEntity->colliderTop->setPos(enemyEntity->colliderTop->x(), enemyEntity->colliderTop->y());

    //set collider list
    QList<QGraphicsItem *> colliding_items_Left = enemyEntity->colliderLeft->collidingItems();
    QList<QGraphicsItem *> colliding_items_Right = enemyEntity->colliderRight->collidingItems();
    QList<QGraphicsItem *> colliding_items_Bottom = enemyEntity->colliderBottom->collidingItems();
    QList<QGraphicsItem *> colliding_items_Top = enemyEntity->colliderTop->collidingItems();

    verifLeft = enemyEntity->colliderVerif(colliding_items_Left, typeid(Wall).name(), typeid(Player).name(), typeid (Enemy).name());
    verifRight = enemyEntity->colliderVerif(colliding_items_Right, typeid (Wall).name(), typeid(Player).name(), typeid (Enemy).name());

    verifBottom = enemyEntity->colliderVerif(colliding_items_Bottom, typeid(Wall).name(), typeid(Player).name(), typeid (Enemy).name());
    verifTop = enemyEntity->colliderVerif(colliding_items_Top, typeid (Wall).name(), typeid(Player).name(), typeid (Enemy).name());

    if(!(verifBottom || verifTop || verifLeft || verifRight)){
        setPos(posDx, posDy);
    }
    else
    {
        if(verifBottom && dy > 0){
            posDy = pos().y();
        }
        else if(verifTop && dy < 0){
            posDy = pos().y();
        }

        if(verifLeft && dx < 0){
            posDx = pos().x();
        }
        else if(verifRight && dx > 0){
            posDx = pos().x();
        }

        setPos(posDx, posDy);
    }
}

//list attack
void Enemy::shootSimple(double argAngle){
    double xPos = parentItem()->x() + x() + enemyEntity->get_xCoordOrigin();
    double yPos = parentItem()->y() + y() + enemyEntity->get_yCoordOrigin();

    double bulletAngleToAdd = 0;

    Projectil * projectil = new Projectil(argAngle + bulletAngleToAdd, xPos, yPos, damage, pathImageProjectil);

    projectil->set_parentName(typeid (Enemy).name());

    game->tabProjectil.append(projectil);

    projectil->setRotation(argAngle + bulletAngleToAdd);
    scene()->addItem(projectil);

    connect(projectil->get_timer(),&QTimer::timeout,projectil,&Projectil::UpdatePosition);
    projectil->get_timer()->start(1000/game->fps);
}

void Enemy::multipleSimpleShoot(double argAngle){
    //initial pos of the bullet
    double xPos = parentItem()->x() + x() + enemyEntity->get_xCoordOrigin();
    double yPos = parentItem()->y() + y() + enemyEntity->get_yCoordOrigin();

    double bulletAngleToAdd = 0;

    //difference of angle between each shoot
    double diffenreceAngle = angleConeAttack / (nbShootAttack - 1);

    double angle = argAngle - angleConeAttack / 2;

    for(int indexBullet = 0; indexBullet < nbShootAttack; ++indexBullet){
        angle += indexBullet * diffenreceAngle;
        Projectil * projectil = new Projectil(angle + bulletAngleToAdd, xPos, yPos, damage, pathImageProjectil);

        projectil->set_parentName(typeid (Enemy).name());

        game->tabProjectil.append(projectil);

        projectil->setRotation(angle + bulletAngleToAdd);
        scene()->addItem(projectil);

        connect(projectil->get_timer(),&QTimer::timeout,projectil,&Projectil::UpdatePosition);
        projectil->get_timer()->start(1000/game->fps);
    }

}

//define parameter attack
void Enemy::set_angleConeAttack(double argAngleCone){
    angleConeAttack = argAngleCone;
}

void Enemy::set_nbShootAttack(int argNbShoot){
    nbShootAttack = argNbShoot;
}

