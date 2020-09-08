#include "EntityCaracter.h"

#include "Game.h"

extern Game * game;

Entity::Entity(){
    //default value
    entityIsPlayer = false;
    displacement = 0;
    health = 0;
    widthEntity = 0;
    heightEntity = 0;
    xCoordOrigin = 0;
    yCoordOrigin = 0;
    widthCollider = 0;
    heightCollider = 0;

    status = 0;

    indexSprite = 0;
}

void Entity::set_PlayerOrEnemy(bool argEntityIsPlayer)
{
    entityIsPlayer = argEntityIsPlayer;
}

bool Entity::get_entityIsPlayer()
{
    return entityIsPlayer;
}

void Entity::set_displacement(int displacementPerSecond, int fps){
    if(displacementPerSecond != 0 && fps != 0){
        displacement = displacementPerSecond / fps;
    }
    else {
        displacement = 0;
    }
}

double Entity::get_displacement(){
    return displacement;
}

void Entity::set_health(double argHealth){
    health = argHealth;
}

double Entity::get_health()
{
    return health;
}

void Entity::set_indexSprite(int argIndexSprite){
    indexSprite = argIndexSprite;
}

void Entity::set_sizeEntity(double argX, double argY){
    widthEntity = argX;
    heightEntity = argY;
}

QPointF Entity::get_pointSizeEntity(){
    return QPointF(widthEntity, heightEntity);
}

double Entity::get_widthEntity(){
    return widthEntity;
}

double Entity::get_heightEntity(){
    return heightEntity;
}

void Entity::set_originEntity(double argXCoord, double argYCoord){
    xCoordOrigin = argXCoord;
    yCoordOrigin = argYCoord;
}

QPointF Entity::get_pointCoordOrgin(){
    return QPointF(xCoordOrigin, yCoordOrigin);
}

double Entity::get_xCoordOrigin(){
    return xCoordOrigin;
}

double Entity::get_yCoordOrigin(){
    return yCoordOrigin;
}

void Entity::set_status(int argStatus){
    status = argStatus;
    changeSprite();
}

int Entity::get_status(){
    return status;
}

void Entity::set_verifRotation(bool argVerif){
    verifRotation = argVerif;
}

bool Entity::get_verifRotation(){
    return verifRotation;
}

void Entity::addSprite(std::string pathFile, int argStatus){
    QPixmap * pixmap = new QPixmap();
    pixmap->load(QString::fromStdString(pathFile));

    if(argStatus == 0){
        spriteIdle.append(pixmap);
    }
    else if(argStatus == 1){
        spriteRun.append(pixmap);
    }
    //add hit

}

void Entity::set_currentSprite(std::string pathFile){
    QPixmap * pixmap = new QPixmap();
    pixmap->load(QString::fromStdString(pathFile));
    currentSprite = pixmap;
}

QPixmap  Entity::get_currentSprite(){
    return *currentSprite;
}

void Entity::changeSprite(){
    indexSprite = 0;
}

void Entity::chooseSprite(){
    if(status == 0){
        updateSprite(spriteIdle);
    }
    else if(status == 1){
        updateSprite(spriteRun);
    }
    else if(status == 2){

    }
}

void Entity::updateSprite(QVector<QPixmap*> tabSprite)
{
    double xPrev = x();
    double yPrev = y();

    prevSprite = currentSprite;
    currentSprite = tabSprite.at(indexSprite);


    if(verifRotation == true){
        QPixmap mirrored = currentSprite->transformed(QTransform().scale(-1,1));
        setPixmap(mirrored);
    }
    else {
        setPixmap(*currentSprite);
    }

    setPos(xPrev ,yPrev + prevSprite->height() - currentSprite->height());

    indexSprite ++;
    if(indexSprite > tabSprite.size() - 1){
        indexSprite = 0;
    }
}

void Entity::set_colliderSize(double argWidth, double argHeight){
    widthCollider = argWidth;
    heightCollider = argHeight;
}

QPointF Entity::get_pointColliderSize(){
    return QPointF(widthCollider, heightCollider);
}

double Entity::get_widthCollider(){
    return widthCollider;
}

double Entity::get_heightCollider(){
    return heightCollider;
}

bool Entity::colliderVerif(QList<QGraphicsItem *> listCollider, QString nameObjectCollide, QString nameObjectCollide_two, QString nameObjectCollide_three)
{
    bool verif = false;
    for (int i = 0, n = listCollider.size(); i < n; ++i){
        if(nameObjectCollide_two == NULL && nameObjectCollide_three == NULL){
             if (typeid(*(listCollider[i])).name() == nameObjectCollide){
                verif = true;
                break;
             }
        }
        else if (nameObjectCollide_two != NULL && nameObjectCollide_three == NULL){
            if (typeid(*(listCollider[i])).name() == nameObjectCollide || typeid(*(listCollider[i])).name() == nameObjectCollide_two){
               verif = true;
               break;
            }
        }
        else {
            if (typeid(*(listCollider[i])).name() == nameObjectCollide || typeid(*(listCollider[i])).name() == nameObjectCollide_two || typeid(*(listCollider[i])).name() == nameObjectCollide_three){
               verif = true;
               break;
            }
        }
    }
    return verif;
}




