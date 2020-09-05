#include "Enemy.h"

#include "Game.h"

#include <QGraphicsScene>
#include <qmath.h> // qSin, qCos, qTan
#include <QDebug>

extern Game * game;

Enemy::Enemy()
{
    //set entity necromancer
    enemyEntity = set_necromancer();

    //distance minimal to player
    distanceMinamalToPlayer = 100;

    prevXPos = 0;
    prevYPos = 0;

}

void Enemy::UpdateEnemy()
{
    enemyEntity->chooseSprite();

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
    if(enemyEntity->get_status() == 1){
        qDebug() << line.length();
        if(line.length() < distanceMinamalToPlayer){
            moveEnemy(-lineInvert.angle());
        }
        else {
            moveEnemy(-line.angle());
        }
    }
}

void Enemy::set_prevPos(QPointF argPrevPos){
    prevXPos = argPrevPos.x();
    prevYPos = argPrevPos.y();
}

void Enemy::set_ToAttackMode(){
    //set entity to attack mode
    enemyEntity->set_status(1);
}

void Enemy::set_objectOfEnemyInScene(){
    setRect(0,0, enemyEntity->get_widthEntity(), enemyEntity->get_heightEntity());
    //setPen(Qt::NoPen);
    //scene()->addItem(enemyEntity);
    scene()->addItem(enemyEntity->colliderBottom);
    scene()->addItem(enemyEntity->colliderTop);
    scene()->addItem(enemyEntity->colliderLeft);
    scene()->addItem(enemyEntity->colliderRight);
}

Entity *Enemy::set_necromancer(){
    //create a new temporary entity
    Entity * entity = new Entity();

    //set entity as enemy
    entity->set_PlayerOrEnemy(false);

    //set the parent of the entity to this class(player)
    entity->setParentItem(this);

    //set displacement
    entity->set_displacement(100, 60);

    //set health
    entity->set_health(25);

    //set status (test)
    entity->set_status(0);

    //set index sprite
    entity->set_indexSprite(0);

    //set value of verifRotationEnemy
    entity->set_verifRotation(true);

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
    entity->colliderBottom->setPos(pos().x() + entity->get_widthEntity()/2 - entity->get_widthCollider()/2, pos().y() +  entity->get_heightEntity() - entity->get_heightCollider());
    entity->colliderTop = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderTop->setPos(pos().x() + entity->get_widthEntity()/2 - entity->get_widthCollider()/2, pos().y());
    entity->colliderLeft = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderLeft->setPos(pos().x() + entity->get_widthCollider(),  pos().y() + entity->get_heightEntity()/2 - entity->get_heightCollider()/2 );
    entity->colliderRight = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderRight->setPos(pos().x() +  entity->get_widthEntity()  - entity->get_widthCollider(), pos().y() + entity->get_heightEntity()/2 - entity->get_heightCollider()/2);

    return entity;
}

void Enemy::moveEnemy(double argAngle){
    double dy = pos().y() + enemyEntity->get_displacement() * qSin(qDegreesToRadians(argAngle));
    double dx = pos().x() + enemyEntity->get_displacement() * qCos(qDegreesToRadians(argAngle));

    setPos(dx, dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();

    bool verifWall = false;
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid (Wall)){
            verifWall = true;
            break;
         }
    }

    if(verifWall){
        setPos(prevXPos, prevYPos);
    }
    else {
        prevXPos = dx;
        prevYPos = dy;
    }


}
