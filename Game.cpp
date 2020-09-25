#include "Game.h"

#include "ListWeapon.h"

#include <QDebug>
#include <chrono>
#include <thread>
#include <QPalette>

Game::Game(QWidget * parent){
    //set fps
    fps = 30;
    //
    verifLeftClick = false;

    //set game is launch to false, because it is the menu
    gameIsReady = false;

    menu = new Menu(width(), height());

    //Create scene
    scene = menu;

    //Minimum size of the screen
    widthScreen = 1000;
    heightScreen = 800;
    setMinimumSize(widthScreen, heightScreen);

    //disable scroll bar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //define scene
    setScene(scene);
    scene->setSceneRect(0,0, width(), height());
    setSceneRect(scene->sceneRect());

    setBackgroundBrush(QBrush(QColor(0, 100, 0)));

    //set playlist to play loop
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Source/Source/Sound/Musique/Menu/Menu.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    //sound menu
    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(40);
    music->play();

    show();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(gameIsReady){
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

        player->weapon->setRotation(angleWeapon);
        player->weapon->entityWeapon->set_angleWeapon(angleWeapon);
    }
}

void Game::resizeEvent(QResizeEvent *event){
    //store the height and the width of the actual screen
    heightScreen = height();
    widthScreen = width();

    //verif if a game is launch
    if(gameIsReady){
        //resize the ui to the size of the screen
        ui->setRect(0,0, widthScreen * 0.2 / 3, heightScreen/3);
        //resize object in UI
        ui->resize();
    }

    //resize the scene rect, set the view's scene rect to this new scene rect
    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2, scene->itemsBoundingRect().size().rheight() + height()/2);
    setSceneRect(scene->sceneRect());
}

void Game::wheelEvent(QWheelEvent *event)
{

}

void Game::mousePressEvent(QMouseEvent *event){
    if(gameIsReady){
        mousePressed_.insert(event->button());
        if(mousePressed_.count(Qt::RightButton)){
            player->weapon->specialShoot();
        }
        if(mousePressed_.count(Qt::LeftButton) && !verifLeftClick){
            player->weapon->simpleShoot();
            verifLeftClick = true;
        }
    }
    else {
        QGraphicsView::mouseReleaseEvent(event);
        //event->accept();
    }
}

void Game::mouseReleaseEvent(QMouseEvent *event){
    if(gameIsReady){
        if(gameIsReady){
            mousePressed_.erase(event->button());
            if(event->button() == Qt::LeftButton){
                verifLeftClick = false;
            }
        }
    }
    else {
        QGraphicsView::mousePressEvent(event);
        //event->accept();
    }
}

void Game::mouseDoubleClickEvent(QMouseEvent *event){
    if(gameIsReady){
        mousePressed_.insert(event->button());
        if(mousePressed_.count(Qt::RightButton)){
            player->weapon->specialShoot();
        }
        if(mousePressed_.count(Qt::LeftButton) && !verifLeftClick){
            player->weapon->simpleShoot();
            verifLeftClick = true;
        }
    }
    else {
        QGraphicsView::mouseDoubleClickEvent(event);
    }
}

bool Game::get_verifRotationCaracter()
{
    return verifRotationCaractere;
}

void Game::openOption(){
    gameIsReady = false;

    timer->stop();

    this->resetMatrix();

    //define new QGraphicsScene pause
    pause = new Pause();

    scene = pause;

    //define scene
    setScene(scene);
    //scene->setSceneRect(0, 0, width(), height());
    setSceneRect(scene->sceneRect());
}

void Game::closeOption(){

    //define scene
    scene = gameScene;

    //define scene
    setScene(scene);
    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2, scene->itemsBoundingRect().size().rheight() + height()/2);
    setSceneRect(scene->sceneRect());

    pause->destructionPause();

    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable, true);
    player->setFocus();

    scale(3,3);

    timer->start();

    gameIsReady = true;
}

void Game::closeGameToRecap(){
    //stop action in game
    gameIsReady = false;

    //stop timer
    timer->stop();

    resetMatrix();

    //destroy game scene
    destroyGameScene();

    recap = new RecapGame();

    scene = recap;

    //define scene
    setScene(scene);
    setSceneRect(scene->sceneRect());
}

void Game::closeRecapToMenu(){
    //stop action in game
    gameIsReady = false;

    //stop timer
    timer->stop();

    menu = new Menu(width(), height());

    scene = menu;

    //set background to background menu
    setBackgroundBrush(QBrush(QColor(0, 100, 0)));

    playlist->removeMedia(0);
    playlist->addMedia(QUrl("qrc:/Source/Source/Sound/Musique/Menu/Menu.mp3"));
    music->play();

    //define scene
    setScene(scene);
    setSceneRect(scene->sceneRect());
}

void Game::launchGame(){

    //Create scene
    gameScene = new QGraphicsScene();

    scene = gameScene;

    gameIsReady = true;

    //set List Weapon
    listWeapon = new ListWeapon();

    //set list enemy
    listEnemy = new ListEnemy();

    //set list boss
    listBoss = new ListBoss();

    //set score to 0
    score = 0;

    //set number of level to 1
    nblevelWorld = 1;

    //setSceneRect(scene->sceneRect());
    setBackgroundBrush(QBrush(QColor(Qt::black)));

    world = new Generation_World();

    scene->addItem(world);

    world->generate();

    for(int indexRoom = 0; indexRoom < world->tabRoom.size(); ++indexRoom){
        if(world->tabRoom.at(indexRoom)->get_type().compare("monsterRoom") == 0){
            world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(),
                                                                world->tabRoom.at(indexRoom)->y()),
                                                        listEnemy->get_sizeTabConstructeurEnemy());
        }
        else if(world->tabRoom.at(indexRoom)->get_type().compare("bossRoom") == 0){
            world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(),
                                                                world->tabRoom.at(indexRoom)->y()),
                                                        listBoss->get_sizeTabConstructeurEnemy());
        }
        else {
            world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(),
                                                                world->tabRoom.at(indexRoom)->y()),
                                                        0);
        }

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

    centerOn(player->x() + player->rect().width()/2 + ((width()*0.2)/3)/2, player->y() + player->rect().height()/2);

    //set player on top of world
    player->setZValue(1);

    //
    player->weapon = new Weapon();

    //add Inventory
    inventory = new Inventory();
    inventory->addFirstWeapon(listWeapon->get_constructeurOnTab(0, player->weapon));

    //add weapon, after creation player and inventory
    player->addWeapon(inventory->get_weapon_1());

    //add weapon (test)
    scene->addItem(player->weapon);
    player->weapon->setParentItem(player);


    //allow the view to recieve mouse informations
    setMouseTracking(true);

    // set the cursor
    //setCursor(QCursor(Qt::CrossCursor));


    //scale the view
    this->scale(3,3);

    //Minimum size of the screen
    setMinimumSize(1000,800);
    widthScreen = 1000;
    heightScreen = 800;

    //disable scroll bar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //define scene
    setScene(scene);
    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2, scene->itemsBoundingRect().size().rheight() + height()/2);
    setSceneRect(scene->sceneRect());

    //divide by three to get actual width and height with the scale
    ui = new UI(width()*0.2/3, height()/3);
    scene->addItem(ui);

    //add update
    timer = new QTimer();

    Update * update = new Update(fps, timer);

    //center view on the player
    this->centerOn(player);


   playlist->removeMedia(0);
   playlist->addMedia(QUrl("qrc:/Source/Source/Sound/Musique/Game/dungeon-theme-the-legend-of-zelda.mp3"));

   music->play();

    menu->destructionMenu();
}

void Game::destroyGameScene(){
    //destroy world
    world->destructionLevel();

    //destruction all projectil
    for(int indexProjectil = tabProjectil.size() - 1; indexProjectil >= 0 ; --indexProjectil){
        delete tabProjectil.takeAt(indexProjectil);
    }
}

void Game::newLevel(){

    //timer stop
    timer->stop();

    //destroy world
    world->destructionLevel();

    //destruction all projectil
    for(int indexProjectil = tabProjectil.size() - 1; indexProjectil >= 0 ; --indexProjectil){
        delete tabProjectil.takeAt(indexProjectil);
    }

    //add 1 level to the counter of level
    nblevelWorld += 1;

    //create a new world
    scene->removeItem(world);
    world = new Generation_World();
    scene->addItem(world);

    //generate it
    world->generate();

    //set every spawn
    for(int indexRoom = 0; indexRoom < world->tabRoom.size(); ++indexRoom){
        if(world->tabRoom.at(indexRoom)->get_type().compare("monsterRoom") == 0){
            world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(),
                                                                world->tabRoom.at(indexRoom)->y()),
                                                        listEnemy->get_sizeTabConstructeurEnemy());
        }
        else if(world->tabRoom.at(indexRoom)->get_type().compare("bossRoom") == 0){
            world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(),
                                                                world->tabRoom.at(indexRoom)->y()),
                                                        listBoss->get_sizeTabConstructeurEnemy());
        }
        else {
            world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(),
                                                                world->tabRoom.at(indexRoom)->y()),
                                                        0);
        }
    }

    //set position of player to the center of the spawn
    player->setPos(100,100);

    //set the scene fo te new world
    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2, scene->itemsBoundingRect().size().rheight() + height()/2);
    setSceneRect(scene->sceneRect());

    //timer start
    timer->start();
}

void Game::addToScore(int argScore){
    score += argScore;
}

int Game::get_score(){
    return score;
}

int Game::get_nbLevelWorld(){
    return nblevelWorld;
}

