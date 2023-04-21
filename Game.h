#pragma once

#include "Enemy.h"

#define NORMAL 1000
//GAME
class Game
{
public:
    Game( SDL_Renderer* gRenderer);
    ~Game();

    void initStage();
    void initPlayer();
    void initMap(string path);
    void initEnemy();
    void initMouse();
    void initSoundGame();
    void initFont();
    void initIng();

    void resetStage();

    int handleEvent();

    int doButton();

    void doKeyBoard();

    void doMouse();

    void updateEnemy();

    void update();

    void render();

    int GameLoop();

    void clearGame();

private:
    //SDL basic variable
    SDL_Renderer* renderer;
    bool gameOver;
    bool pause;
    SDL_Event e;

    //entity
    Player* player;
    Map gMap;
    SDL_Point camera;
    Mouse* mouse;

    //Weapon
    Bullet* tempBullet;

    //enemies
    EnemyMelee* tempEnemyMelee;
    vector <EnemyMelee*> enemy_list;


    //count time
    Uint64 currentTime;

    //score
    int score;

    //sound
    Mix_Chunk* enemy_die;
    Mix_Music* bgMusic;

    //ing button
    Button Ing_Button[ING_TOTAL];

    //font
    Word score_word;
};


