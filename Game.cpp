#include "Game.h"

#include "ListWeapon.h"

#include <QDebug>

Game::Game(QWidget * parent){
    //set fps
    fps = 30;
    //
    verifLeftClick = false;

    //set List Weapon
    listWeapon = new ListWeapon();

    //set list enemy
    listEnemy = new ListEnemy();

    //set list boss
    listBoss = new ListBoss();

    //Create scene
    scene = new QGraphicsScene();
    //setSceneRect(scene->sceneRect());
    setBackgroundBrush(QBrush(QColor(Qt::white)));

    world = new Generation_World();

    scene->addItem(world);

    world->generate();

    for(int indexRoom = 0; indexRoom < world->tabRoom.size(); ++indexRoom){
        world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(), world->tabRoom.at(indexRoom)->y()), listEnemy->get_sizeTabConstructeurEnemy());
    }

    //add Inventory
    inventory = new Inventory();
    inventory->addFirstWeapon(listWeapon->get_constructeurOnTab(0));

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

    //set level visibility of player to be above world
    player->setZValue(1);

    //add weapon, after creation player and inventory
    player->addWeapon(inventory->get_weapon_1());

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
    widthScreen = 1000;
    heightScreen = 800;

    //disable scroll bar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui = new UI(widthScreen*0.2/3, heightScreen/3);
    scene->addItem(ui);


    //define scene
    setScene(scene);
    setSceneRect(scene->sceneRect());

    show();

    //add update
    timer = new QTimer();

    Update * update = new Update(fps, timer);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    //line to get angle from player
    QPointF pt1(mapFromScene(QPoint(player->x() + player->rect().width()/2,
                                    player->y() + player->rect().height()/2 )));
    QPointF pt2(event->pos());
    QLineF line(pt1,pt2);
    double asbAngle = abs(-1 * line.angle());
    double angle = -1 * line.angle();
    //line to get angle from weapon
    QPointF pt1Weapon(mapFromScene(QPoint(player->weapon->test_ouputWeapon->scenePos().x(),
                                          player->weapon->test_ouputWeapon->scenePos().y())));
    QPointF pt2Weapon(event->pos());
    QLineF lineAngleWeapon(pt1Weapon,pt2Weapon);
    double angleWeapon = -1 * lineAngleWeapon.angle();

    if(90 < asbAngle && asbAngle < 270 && player->playerEntity->get_verifRotation() == false){
        player->playerEntity->setPixmap(player->playerEntity->get_currentSprite().transformed(QTransform().scale(-1,1)));
        player->playerEntity->set_verifRotation(true);
        player->weapon->setPos(player->weapon->entityWeapon->get_posWeaponInvert());
        player->weapon->entityWeapon->turnWeapon(true);
        orientationWeapon = -180 - 60;

    }
    else if((asbAngle < 90 || 270 < asbAngle) && player->playerEntity->get_verifRotation() == true){
        player->playerEntity->setPixmap(player->playerEntity->get_currentSprite());
        player->playerEntity->set_verifRotation(false);
        player->weapon->setPos(player->weapon->entityWeapon->get_posWeapon());
        player->weapon->entityWeapon->turnWeapon(false);
        orientationWeapon = 60;
    }

    player->weapon->setRotation(angle);
    player->weapon->entityWeapon->set_angleWeapon(angleWeapon);
}

void Game::resizeEvent(QResizeEvent *event){
    //
    heightScreen = height();
    widthScreen = width();
    ui->setRect(0,0, widthScreen * 0.2 / 3, heightScreen/3);
    //resize object in UI
    ui->resize();

    //resize the scene rect, set the view's scene rect to this new scene rect
    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2, scene->itemsBoundingRect().size().rheight() + height()/2);
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

void Game::mouseDoubleClickEvent(QMouseEvent *event){
    mousePressed_.insert(event->button());
    if(mousePressed_.count(Qt::RightButton)){
        player->weapon->specialShoot();
    }
    if(mousePressed_.count(Qt::LeftButton) && !verifLeftClick){
        player->weapon->simpleShoot();
        verifLeftClick = true;
    }
}

bool Game::get_verifRotationCaracter()
{
    return verifRotationCaractere;
}

void Game::newLevel(){
    //world->destructionLevel();

    //timer stop to not interfer with the destruction of the world
    timer->stop();

    //destruction old world
    world->destructionLevel();

    //destruciton of all old bullet
    for(int indexProjectil = tabProjectil.size() - 1; 0 <= indexProjectil; --indexProjectil){
        tabProjectil.takeAt(indexProjectil)->destructionProjectil();
        //tabProjectil.remove(indexProjectil);
    }

    scene->removeItem(world);
    world = new Generation_World();
    scene->addItem(world);

    world->generate();

    for(int indexRoom = 0; indexRoom < world->tabRoom.size(); ++indexRoom){
        world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(), world->tabRoom.at(indexRoom)->y()), listEnemy->get_sizeTabConstructeurEnemy());
    }

    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2, scene->itemsBoundingRect().size().rheight() + height()/2);
    setSceneRect(scene->sceneRect());

    player->setPos(100,100);

    timer->start();
}

