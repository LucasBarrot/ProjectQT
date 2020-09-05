#include "Game.h"


#include <QDebug>


Game::Game(QWidget * parent){
    //set fps
    fps = 30;
    //
    verifLeftClick = false;

    //Create scene
    scene = new QGraphicsScene();

    //setSceneRect(scene->sceneRect());
    setBackgroundBrush(QBrush(QColor(Qt::black)));

    world = new Generation_World();

    scene->addItem(world);

    world->generate();

    for(int indexRoom = 0; indexRoom < world->tabRoom.size(); ++indexRoom){
        world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(), world->tabRoom.at(indexRoom)->y()));
    }

    //add player
    player = new Player(fps);
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable, true);
    player->setFocus();
    //set the position of the player
    player->setPos(95,95);
    // add the player to the scene
    scene->addItem(player);
    player->set_objectOfPlayerInScene();

    //add weapon (test)
    scene->addItem(player->weapon);
    player->weapon->setParentItem(player);

    //allow the view to recieve mouse informations
    setMouseTracking(true);

    // set the cursor
    //setCursor(QCursor(Qt::CrossCursor));

    //center view on the player
    this->centerOn(player);
    //scale the view
    this->scale(3,3);

    //Minimum size of the screen
    setMinimumSize(1000,800);

    //disable scroll bar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //define scene
    setScene(scene);
    setSceneRect(scene->sceneRect());

    //add update
    Update * update = new Update(fps);

    show();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    //line to get angle from player
    QPointF pt1(width()/2, height()/2);
    QPointF pt2(event->pos());
    QLineF line(pt1,pt2);
    double asbAngle = abs(-1 * line.angle());
    double angle = -1 * line.angle();
    //line to get angle from weapon
    QPointF pt1Weapon(mapFromScene(QPoint(player->x() + player->rect().width()/2 + player->weapon->get_lineRotationWeapon().p2().x(),
                                          player->y() + player->rect().height()/2 + player->weapon->get_lineRotationWeapon().p2().y())));
    QPointF pt2Weapon(event->pos());
    QLineF lineAngleWeapon(pt1Weapon,pt2Weapon);
    double angleWeapon = -1 * lineAngleWeapon.angle();

    if(90 < asbAngle && asbAngle < 270 && player->playerEntity->get_verifRotation() == false){
        player->playerEntity->setPixmap(player->playerEntity->get_currentSprite().transformed(QTransform().scale(-1,1)));
        player->playerEntity->set_verifRotation(true);
        player->weapon->setPos(0,10);
        player->weapon->set_lineNewPositionWeapon(QPointF(0,10));
        orientationWeapon = -180 - 60;

    }
    else if((asbAngle < 90 || 270 < asbAngle) && player->playerEntity->get_verifRotation() == true){
        player->playerEntity->setPixmap(player->playerEntity->get_currentSprite());
        player->playerEntity->set_verifRotation(false);
        player->weapon->setPos(16-4,10);
        player->weapon->set_lineNewPositionWeapon(QPointF(16-4,10));
        orientationWeapon = 60;
    }

    player->weapon->setRotation(angle + orientationWeapon);
    player->weapon->set_lineRotationWeapon(angle);
    player->weapon->set_angleAiming(angleWeapon);
}

void Game::resizeEvent(QResizeEvent *event){
    //resize the scene rect, set the view's scene rect to this new scene rect
    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2,scene->itemsBoundingRect().size().rheight() + height()/2);
    setSceneRect(scene->sceneRect());
}

void Game::wheelEvent(QWheelEvent *event)
{

}

void Game::mousePressEvent(QMouseEvent *event){
    mousePressed_.insert(event->button());
    if(mousePressed_.count(Qt::RightButton)){
        player->weapon->specialShoot();
    }
    if(mousePressed_.count(Qt::LeftButton) && !verifLeftClick){
        player->weapon->simpleShoot();
        verifLeftClick = true;
    }
}

void Game::mouseReleaseEvent(QMouseEvent *event){
    mousePressed_.erase(event->button());
    if(event->button() == Qt::LeftButton){
        verifLeftClick = false;
    }
}

void Game::mouseDoubleClickEvent(QMouseEvent *event)
{

}

bool Game::get_verifRotationCaracter()
{
    return verifRotationCaractere;
}
