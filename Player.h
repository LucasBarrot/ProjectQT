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

    //update Sprite for each frame
    void updateSprite();

    QPixmap get_currentSprite();

    //Collider
    Collider * colliderBottom;
    Collider * colliderTop;
    Collider * colliderLeft;
    Collider * colliderRight;


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
    //Size of player
    double xSize_player;
    double ySize_player;
    //Size of collider
    double xSize_Collider;
    double ySize_Collider;
    //
    double xCoordOrigin;
    double yCoordOrigin;
    //of pixel the caracter move
    double speed;
    //angle
    double angle;
    //QSet<int> keysPressed_;
    std::set<int> keysPressed_;

    //status caracter
    // status = 0 : idle
    //status = 1: move
    //status = 3 : hit
    int status;

    //index Sprite play;
    int indexSprite;

    //add Sprite
    QPixmap * addSprite(std::string pathFile);

    //current sprite
    QPixmap * currentSprite;

    //sprite
    QVector<QPixmap*> spriteIdle;
    QList<QImage *> spriteRun;
    QList<QImage *> spriteHit;

    bool colliderVerif(QList<QGraphicsItem *> listCollider);
    void moveCloseToWall(int xSign, int ySign, Collider * collider);


};

#endif // PLAYER_H
