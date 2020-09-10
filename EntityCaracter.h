#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "Collider.h"

class Entity : public QGraphicsPixmapItem {
public:
    Entity();

    //Enemy or player
    void set_PlayerOrEnemy(bool argEntityIsPlayer);
    bool get_entityIsPlayer();

    //displacement
    void set_displacement(int displacementPerSecond,int fps);
    double get_displacement();

    //health
    void set_health(double argHealth);
    double get_health();

    //set index sprite
    void set_indexSprite(int argIndexSprite);

    //size entity
    void set_sizeEntity(double argX, double argY);
    QPointF get_pointSizeEntity();
    double get_widthEntity();
    double get_heightEntity();

    //origin entity
    void set_originEntity(double argXCoord, double argYCoord);
    QPointF get_pointCoordOrgin();
    double get_xCoordOrigin();
    double get_yCoordOrigin();

    //status
    //set status
    void set_status(int argStatus);
    int get_status();

    //verif angle entity to modify or not the direction of entity
    void set_verifRotation(bool argVerif);
    bool get_verifRotation();

    // Sprite :
    //add Sprite
    void addSprite(std::string pathFile, int argStatus);
    //set current sprite
    void set_currentSprite(std::string pathFile);
    //get current sprite
    QPixmap get_currentSprite();
    //change the animation we play
    void changeSprite();
    //choose animation to play depending on the status
    void chooseSprite();
    //update Sprite for each frame
    void updateSprite(QVector<QPixmap*> tabSprite);

    //Collider
    //collider size
    void set_colliderSize(double argWidth, double argHeight);
    QPointF get_pointColliderSize();
    double get_widthCollider();
    double get_heightCollider();

    //verif if player not collid with
    bool colliderVerif(QList<QGraphicsItem *> listCollider, QString nameObjectCollide, QString nameObjectCollide_two = NULL, QString nameObjectCollide_three = NULL);

    //collider object
    Collider * colliderBottom;
    Collider * colliderTop;
    Collider * colliderLeft;
    Collider * colliderRight;

private:
    //Player or Enemy
    bool entityIsPlayer;

    //displacement entity
    double displacement;

    //health
    double health;

    //Size of entity
    double widthEntity;
    double heightEntity;

    //Origin entity
    double xCoordOrigin;
    double yCoordOrigin;

    //Size of collider
    double widthCollider;
    double heightCollider;

    //verif the rotation of enemy
    bool verifRotation;

    //status caracter
    // status = 0 : idle
    //status = 1: move(player) or attack mode (enemy)
    //status = 2 : hit
    int status;

    //index Sprite play;
    int indexSprite;

    //current sprite
    QPixmap * currentSprite;
    QPixmap * prevSprite;

    //sprite
    QVector<QPixmap*> spriteIdle;
    QVector<QPixmap*> spriteRun;
    QVector<QPixmap*> spriteHit;

};

#endif // ENTITY_H
