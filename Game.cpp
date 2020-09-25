#include "Game.h"
#include "World.h"
#include <QDebug>
#include <array>
#include <QPolygonF>

Game::Game(QWidget * parent){
    //set fps
    fps = 30;
    //
    verifLeftClick = false;

    //Create scene
    scene = new QGraphicsScene();
    //define scene
    setScene(scene);
    //setSceneRect(scene->sceneRect());

    std::vector<int> multiples{ 64, 80, 96, 112, 128, 144, 160, 176, 192, 208};

    //setSceneRect(scene->sceneRect());
    double room1_x = rand() % 800, room1_y = rand() % 600;
    double room2_x = rand() % 800, room2_y = rand() % 600;

    double room1_height = multiples[rand() % multiples.size()];
    double room1_width = multiples[rand() % multiples.size()];

    double room2_height = multiples[rand() % multiples.size()];
    double room2_width = multiples[rand() % multiples.size()];

    //setBackgroundBrush(QBrush(QColor(Qt::black)));
    Room * room1 = new Room(room1_x,room1_y,room1_height,room1_width);
    Room * room2 = new Room(room2_x,room2_y,room2_height,room2_width);

    World *world = new World(room1, room2);

    int NUMBER_OF_ROOMS = 10; // resulat +2

    double room_x = rand() % 800, room_y = rand() % 600;
    double room_height = multiples[rand() % multiples.size()];
    double room_width  = multiples[rand() % multiples.size()];
    Room * room = new Room(room_x,room_y,room_width,room_height);

    for(int i=0; i<NUMBER_OF_ROOMS; i++){
        while (world->intersect(* room)) {

            double room_x = rand() % 800, room_y = rand() % 600;
            double room_height = multiples[rand() % multiples.size()];
            double room_width  = multiples[rand() % multiples.size()];

            room =  new Room(room_x,room_y,room_width,room_height);
        }
       world->connect(room);
    }

    scene->addItem(world);




    //set all grounds of rooms
    for(Room * room : world->rooms_in_net){
        room->add_ground(scene);
        room->add_walls(scene);
        }

    for(Hallway tun : world->hallways_list){
        tun.set_horizontal_arm(scene);
        tun.set_vertical_arm(scene);
        tun.set_elbow(scene);

    }
    //Ground *img2 = new Ground(1,2,7);
    //QPixmap img(":/Source/Source/Image/Ground/Ground_1.png");
   // scene->addItem(img2);
    //tile->setPos( x, y );

    //world->generate();


/*
    for(int indexRoom = 0; indexRoom < world->tabRoom.size(); ++indexRoom){
        world->tabRoom.at(indexRoom)->set_spawnZone(QPointF(world->tabRoom.at(indexRoom)->x(), world->tabRoom.at(indexRoom)->y()));
    }
*/
    /*
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

*/
    ui = new UI();

    //scene->addItem(ui);

    //ui->printOnScreen();




    //add update
    //Update * update = new Update(fps);

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
    QPointF pt1Weapon(mapFromScene(QPoint(player->x() + player->rect().width()/2 + player->weapon->entityWeapon->get_lineRotationWeapon().p2().x(),
                                          player->y() + player->rect().height()/2 + player->weapon->entityWeapon->get_lineRotationWeapon().p2().y())));
    QPointF pt2Weapon(event->pos());
    QLineF lineAngleWeapon(pt1Weapon,pt2Weapon);
    double angleWeapon = -1 * lineAngleWeapon.angle();

    if(90 < asbAngle && asbAngle < 270 && player->playerEntity->get_verifRotation() == false){
        player->playerEntity->setPixmap(player->playerEntity->get_currentSprite().transformed(QTransform().scale(-1,1)));
        player->playerEntity->set_verifRotation(true);
        player->weapon->setPos(0,10);
        player->weapon->entityWeapon->turnWeapon(true);
        orientationWeapon = -180 - 60;

    }
    else if((asbAngle < 90 || 270 < asbAngle) && player->playerEntity->get_verifRotation() == true){
        player->playerEntity->setPixmap(player->playerEntity->get_currentSprite());
        player->playerEntity->set_verifRotation(false);
        player->weapon->setPos(16-4,10);
        player->weapon->entityWeapon->turnWeapon(false);
        orientationWeapon = 60;
    }

    player->weapon->setRotation(angle + orientationWeapon);
    player->weapon->entityWeapon->set_lineRotationWeapon(angle);
    player->weapon->entityWeapon->set_angleWeapon(angleWeapon);
}

void Game::resizeEvent(QResizeEvent *event){
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
