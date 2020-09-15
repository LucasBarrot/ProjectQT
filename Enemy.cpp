#include "Enemy.h"

#include "Game.h"

#include <QGraphicsScene>
#include <qmath.h> // qSin, qCos, qTan
#include <QDebug>
#include <random>

extern Game * game;

Enemy::Enemy()
{
    //set entity necromancer
    enemyEntity = set_necromancer();

    //distance minimal to player
    distanceMinamalToPlayer = 100;

    prevXPos = 0;
    prevYPos = 0;

    shootSimpleReady = true;

    lineOfSight = new QGraphicsRectItem();
    lineOfSight->setParentItem(this);
    lineOfSight->setPen(Qt::NoPen);
}

void Enemy::UpdateEnemy(){
    if(enemyEntity->get_displacement() == 0){
        enemyEntity->set_displacement(100, game->fps);
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
                shootSimpleReady = false;
                QTimer::singleShot(5000, this, &Enemy::updateShootSimple);

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
    setRect(0,0, enemyEntity->get_widthEntity(), enemyEntity->get_heightEntity());

    enemyEntity->colliderBottom->setParentItem(this);
    enemyEntity->colliderTop->setParentItem(this);
    enemyEntity->colliderLeft->setParentItem(this);
    enemyEntity->colliderRight->setParentItem(this);
}




Entity *Enemy::set_necromancer(){
    //create a new temporary entity
    Entity * entity = new Entity();

    //set entity as enemy
    entity->set_PlayerOrEnemy(false);

    //set the parent of the entity to this class(player)
    //entity->setParentItem(this);

    //set displacement
    entity->set_displacement(0, 0);

    //set health
    entity->set_maxHealth(25);
    entity->set_actualHealth(entity->get_maxHealth());

    //set status (test)
    entity->set_status(0);

    //set index sprite
    entity->set_indexSprite(0);

    //set value of verifRotationEnemy
    entity->set_verifRotation(true);

    //define parent
    entity->setParentItem(this);

    //set invulnerability to true
    entity->set_invulnerability(true);

    //set Sprite entity
    //Sprite idle
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f0.png", 0);
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f1.png", 0);
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f2.png", 0);
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f3.png", 0);
    //Sprite Run
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f0.png", 1);
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f1.png", 1);
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f2.png", 1);
    entity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f3.png", 1);

    //set Current Sprite
    entity->set_currentSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f0.png");

    //set size entity
    entity->set_sizeEntity(entity->get_currentSprite().width(), entity->get_currentSprite().height());

    //set entity coord
    entity->set_originEntity(entity->get_widthEntity() / 2, entity->get_heightEntity() / 2);

    //set collider
    //set size collider
    entity->set_colliderSize(2, 2);
    //position
    entity->colliderBottom = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderBottom->setPos(pos().x() + entity->get_widthEntity()/2 - entity->get_widthCollider()/2, pos().y() +  entity->get_heightEntity() + entity->get_heightCollider() * 0.5);
    entity->colliderTop = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderTop->setPos(pos().x() + entity->get_widthEntity()/2 - entity->get_widthCollider()/2, pos().y() - entity->get_heightCollider() * 1.5);
    entity->colliderLeft = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderLeft->setPos(pos().x() - entity->get_widthCollider() * 1.5,  pos().y() + entity->get_heightEntity()/2 - entity->get_heightCollider()/2 );
    entity->colliderRight = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderRight->setPos(pos().x() +  entity->get_widthEntity()  + entity->get_widthCollider() * 0.5, pos().y() + entity->get_heightEntity()/2 - entity->get_heightCollider()/2);

    //Path image projectil shooted by enemy
    pathImageProjectil = ":/Source/Source/Image/projectil/Projectil_1.png";

    return entity;
}

void Enemy::shootSimple(double angle){
    double xPos = parentItem()->x() + x() + enemyEntity->get_xCoordOrigin();
    double yPos = parentItem()->y() + y() + enemyEntity->get_yCoordOrigin();

    double bulletAngleToAdd = 0;

    Projectil * projectil = new Projectil(angle + bulletAngleToAdd, xPos, yPos, 15, pathImageProjectil);

    projectil->set_parentName(typeid (Enemy).name());

    game->tabProjectil.append(projectil);

    projectil->setRotation(angle + bulletAngleToAdd);
    scene()->addItem(projectil);

    connect(projectil->get_timer(),&QTimer::timeout,projectil,&Projectil::UpdatePosition);
    projectil->get_timer()->start(1000/game->fps);
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
