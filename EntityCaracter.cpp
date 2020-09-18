#include "EntityCaracter.h"

#include "Game.h"

extern Game * game;

EntityCaracter::EntityCaracter(){
    //default value
    TypeCaracter = "";
    displacement = 0;
    actualHealth = 0;
    maxHealth = 0;
    widthEntity = 0;
    heightEntity = 0;
    xCoordOrigin = 0;
    yCoordOrigin = 0;
    widthCollider = 0;
    heightCollider = 0;

    status = 0;

    indexSprite = 0;
}

void EntityCaracter::set_PlayerOrEnemy(QString argTypePlayer){
    TypeCaracter = argTypePlayer;
}

QString EntityCaracter::get_entityIsPlayer(){
    return TypeCaracter;
}

void EntityCaracter::set_displacement(int displacementPerSecond, int fps){
    if(displacementPerSecond != 0 && fps != 0){
        displacement = displacementPerSecond / fps;
    }
    else {
        displacement = 0;
    }
}

double EntityCaracter::get_displacement(){
    return displacement;
}

void EntityCaracter::set_actualHealth(double argHealth){
    actualHealth = argHealth;
}

double EntityCaracter::get_actualHealth()
{
    return actualHealth;
}

void EntityCaracter::set_maxHealth(double argHealth){
    maxHealth = argHealth;
}

double EntityCaracter::get_maxHealth()
{
    return maxHealth;
}

void EntityCaracter::set_indexSprite(int argIndexSprite){
    indexSprite = argIndexSprite;
}

void EntityCaracter::set_sizeEntity(double argX, double argY){
    widthEntity = argX;
    heightEntity = argY;
}

QPointF EntityCaracter::get_pointSizeEntity(){
    return QPointF(widthEntity, heightEntity);
}

double EntityCaracter::get_widthEntity(){
    return widthEntity;
}

double EntityCaracter::get_heightEntity(){
    return heightEntity;
}

void EntityCaracter::set_originEntity(double argXCoord, double argYCoord){
    xCoordOrigin = argXCoord;
    yCoordOrigin = argYCoord;
}

QPointF EntityCaracter::get_pointCoordOrgin(){
    return QPointF(xCoordOrigin, yCoordOrigin);
}

double EntityCaracter::get_xCoordOrigin(){
    return xCoordOrigin;
}

double EntityCaracter::get_yCoordOrigin(){
    return yCoordOrigin;
}

void EntityCaracter::set_status(int argStatus){
    status = argStatus;
    changeSprite();
}

int EntityCaracter::get_status(){
    return status;
}

void EntityCaracter::set_verifRotation(bool argVerif){
    verifRotation = argVerif;
}

bool EntityCaracter::get_verifRotation(){
    return verifRotation;
}

void EntityCaracter::set_invulnerability(bool argInvulnerability){
    invulnerability = argInvulnerability;
}

bool EntityCaracter::get_invulnerability(){
    return invulnerability;
}

//sprite
void EntityCaracter::addSprite(std::string pathFile, int argStatus){
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

void EntityCaracter::set_currentSprite(std::string pathFile){
    if(pathFile == ""){
        currentSprite = spriteIdle.at(0);
    }
    else {
        QPixmap * pixmap = new QPixmap();
        pixmap->load(QString::fromStdString(pathFile));
        currentSprite = pixmap;
    }

}

QPixmap  EntityCaracter::get_currentSprite(){
    return *currentSprite;
}

void EntityCaracter::changeSprite(){
    indexSprite = 0;
}

void EntityCaracter::chooseSprite(){
    if(status == 0){
        updateSprite(spriteIdle);
    }
    else if(status == 1){
        updateSprite(spriteRun);
    }
    else if(status == 2){

    }
}

void EntityCaracter::updateSprite(QVector<QPixmap*> tabSprite)
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


//collider
void EntityCaracter::set_colliderSize(double argWidth, double argHeight){
    widthCollider = argWidth;
    heightCollider = argHeight;
}

QPointF EntityCaracter::get_pointColliderSize(){
    return QPointF(widthCollider, heightCollider);
}

double EntityCaracter::get_widthCollider(){
    return widthCollider;
}

double EntityCaracter::get_heightCollider(){
    return heightCollider;
}

bool EntityCaracter::colliderVerif(QList<QGraphicsItem *> listCollider, QString nameObjectCollide, QString nameObjectCollide_two, QString nameObjectCollide_three)
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




