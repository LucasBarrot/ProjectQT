#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "Collider.h"

class EntityCaracter : public QGraphicsPixmapItem {
public:
    EntityCaracter();

    //Enemy or player
    void set_PlayerOrEnemy(QString argType);
    QString get_entityIsPlayer();

    //displacement
    void set_displacement(int displacementPerSecond,int fps);
    double get_displacement();

    //health
    void set_actualHealth(double argHealth);
    double get_actualHealth();
    void set_maxHealth(double argHealth);
    double get_maxHealth();

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

    //invulnerability
    void set_invulnerability(bool argInvulnerability);
    bool get_invulnerability();

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
    QString TypeCaracter;

    //displacement entity
    double displacement;

    //health
    double actualHealth;
    double maxHealth;

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

    //invulnerability
    //if true enemy can't die
    //if false enemy can die
    bool invulnerability;

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
