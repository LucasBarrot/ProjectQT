#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <set>
#include <QObject>


#include "Collider.h"
#include "Weapon.h"


class Player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(double fps);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

    void moving();

    QPointF getOrigin();

    void set_angle(double angle);

    double get_angle();

    //Collider
    Collider * colliderBottom;
    Collider * colliderTop;
    Collider * colliderLeft;
    Collider * colliderRight;

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
    //Size of player
    double xSize_player;
    double ySize_player;
    //Size of collider
    double xSize_Collider;
    double ySize_Collider;
    //
    double xCoordOrigin;
    double yCoordOrigin;
    double x_prev;
    double y_prev;
    //of pixel the caracter move
    double speed;
    //angle
    double angle;
    //QSet<int> keysPressed_;
    std::set<int> keysPressed_;

    bool colliderVerif(QList<QGraphicsItem *> listCollider);
    void moveCloseToWall();


};

#endif // PLAYER_H
