#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Generation_World.h"
#include "Player.h"
#include "Update.h"
#include "Projectil.h"
#include "UI.h"
#include "Inventory.h"
#include "ListWeapon.h"
#include "ListEnemy.h"
#include "ListBoss.h"
#include "Menu.h"
#include "Pause.h"
#include "RecapGame.h"


class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    void mouseMoveEvent(QMouseEvent * event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    bool get_verifRotationCaracter();

    QGraphicsScene * scene;
    Generation_World * world;
    Player * player;
    UI * ui;
    Inventory * inventory;
    ListWeapon * listWeapon;
    ListEnemy * listEnemy;
    ListBoss * listBoss;
    QMediaPlaylist *playlist;
    QMediaPlayer * music;

    QVector<Projectil*> tabProjectil;

    std::set<int> mousePressed_;

    double fps;

    //height and width screen
    double heightScreen;
    double widthScreen;

    //option
    //open option menu
    void openOption();
    //close option
    void closeOption();

    //close game to recap
    void closeGameToRecap();

    //close recap
    void closeRecapToMenu();

    //new level
    void newLevel();

    QTimer *timer;

    //monster kill add to score
    void addToScore(int argScore);
    int get_score();

    //get number of level covered by the player
    int get_nbLevelWorld();

public slots:
    //launch a game
    void launchGame();

private:
    //orientation of the weapon
    double orientationWeapon;

    bool verifRotationCaractere = true;

    bool verifLeftClick;

    //verif if a game is launch
    bool gameIsReady;

    //set first weapon
    void addFirstWeaponToInventory();

    Pause * pause;
    Menu * menu;
    QGraphicsScene * gameScene;
    RecapGame * recap;

    //Number of level traveled
    int nblevelWorld;

    //score
    int score;

    //destroy game scene
    void destroyGameScene();
};

#endif // GAME_H
