#include "Bullet.h"
#include "Game.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QList>

extern Game * game;

Bullet::Bullet(QObject *parent) : QObject(parent), QGraphicsRectItem(){



    // drew the rect
    setRect(0,0,10,50);

    //emit a signal on every times up
    QTimer * timer = new QTimer();

    // connect
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);

}

void Bullet::move(float dx, float dy){

    // move bullet up
    rect().translate(dy,dx);

}

