#include "Game.h"


#include <QDebug>


Game::Game(QWidget * parent){
    //set fps
    fps = 30;
    //Create scene
    scene = new QGraphicsScene();

    //setSceneRect(scene->sceneRect());
    setBackgroundBrush(QBrush(QColor(Qt::black)));

    world = new Generation_World();

    scene->addItem(world);

    world->generate();

    //add player
    player = new Player(fps);
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable, true);
    player->setFocus();
    //set the position of the player
    player->setPos(95,95);
    // add the player to the scene
    scene->addItem(player);
    scene->addItem(player->colliderBottom);
    scene->addItem(player->colliderTop);
    scene->addItem(player->colliderRight);
    scene->addItem(player->colliderLeft);

    //add weapon (test)
    scene->addItem(player->weapon);
    player->weapon->setPos(16-4,10);
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

    //add update
    Update * update = new Update(fps);

    //define scene
    setScene(scene);
    setSceneRect(scene->sceneRect());


    show();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pt1(width()/2, height()/2);
    QPointF pt2(event->pos());
    QLineF line(pt1,pt2);
    double asbAngle = abs(-1 * line.angle());
    double angle = -1 * line.angle();

    if(90 < asbAngle && asbAngle < 270 && verifRotationCaractere == false){
        QImage img(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f0_resize.png");
        img = img.mirrored(true, false);
        player->setPixmap(player->get_currentSprite().transformed(QTransform().scale(-1,1)));
        player->verifMirroredSprite = true;
        verifRotationCaractere = true;

        player->weapon->setPos(0,10);
        orientationWeapon = -180 - 60;

    }
    else if((asbAngle < 90 || 270 < asbAngle) && verifRotationCaractere == true){
        QImage img(":/Source/Source/Image/Caractere/wizzard_m_idle_anim_f0_resize.png");
        player->setPixmap(player->get_currentSprite());
        player->verifMirroredSprite = false;
        verifRotationCaractere = false;
        player->weapon->setPos(16-4,10);
        orientationWeapon = 60;
    }

    player->weapon->setRotation(angle + orientationWeapon);
    player->set_angle(angle);

}

void Game::resizeEvent(QResizeEvent *event){
    //resize the scene rect, set the view's scene rect to this new scene rect
    qDebug() <<"width : " << width() << "height : " << height();
    scene->setSceneRect(scene->itemsBoundingRect().x() - width()/4, scene->itemsBoundingRect().y() - height()/4,scene->itemsBoundingRect().size().rwidth() + width()/2,scene->itemsBoundingRect().size().rheight() + height()/2);
    setSceneRect(scene->sceneRect());
}

void Game::wheelEvent(QWheelEvent *event)
{

}

void Game::mousePressEvent(QMouseEvent *event){
    mousePressed_.insert(event->button());
    if(mousePressed_.size() == 1){
        player->weapon->Shoot();
    }
}

void Game::mouseReleaseEvent(QMouseEvent *event){
    mousePressed_.erase(event->button());
}

void Game::mouseDoubleClickEvent(QMouseEvent *event)
{

}

bool Game::get_verifRotationCaracter()
{
    return verifRotationCaractere;
}
