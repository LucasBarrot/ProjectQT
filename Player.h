#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <set>
#include <QObject>
#include <QGraphicsObject>

#include "Weapon.h"
#include "Entity.h"
#include "SpawnZone.h"


class Player: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Player(double fps);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

    //move caracter
    void moving();

    //check if player is in a room
    void verifPlayerInRoom();

    //get origin of player
    QPointF getOriginMapToScene();

    //set the angle of player
    void set_angle(double angle);

    //player is in room
    SpawnZone * get_playerIsInRoom();

    //return angle of player
    double get_angle();

    //set entity player
    Entity * playerEntity;

    //set in scene object of player (playerEntity and collider)
    void set_objectOfPlayerInScene();

    //verif rotation sprite (test)
    bool verifMirroredSprite = false;

    //Weapon (test)
    Weapon * weapon;
signals:
    /// Emitted when a key is pressed.
    /// @param key Integer describing the key that was pressed. Compare with constants in Qt::key_.
    void keyPressed(int key);

    /// Emitted when a key is released.
    /// @param key Integer describing the key that was released. Compare with constants in Qt::key_.
    void keyReleased(int key);
private:    
    //angle
    double angle;
    //QSet<int> keysPressed_;
    std::set<int> keysPressed_;
    //verif if a key as been stroke
    bool verifFirstKeyMOuvement;

    //define entity player;
    Entity * set_entityPlayer(int player);

    //To know in wich room is the player
    SpawnZone * playerIsInRoom;

    //verif if player not collid with
    bool colliderVerif(QList<QGraphicsItem *> listCollider);

    void moveCloseToWall(int xSign, int ySign, Collider * collider);


};

#endif // PLAYER_H
