#pragma once

#include "Enemy.h"
#include "Word.h"

#define NORMAL 1000

//GAME
class Game
{
public:
    Game(Resource* _res);
    ~Game();

    void initStage();
    void initPlayer();

    void resetStage();

    int handleEvent();

    int doButton();

    void doKeyBoard();

    void doMouse();

    void updateEnemy();

    void update();

    void drawButtons();

    void drawEnemyMelee();

    void drawEnemyRanged();

    void drawEnemy();

    void drawPlayer();

    void drawMap();

    void drawPoint();

    void drawMouse();

    void render();

    int GameLoop();

    void clearGame();

private:
    Resource* res;

    bool gameOver;
    bool pause;
    SDL_Event e;

    //entity
    Player* player;
    Map* gMap;
    Vec2f camera;

    //enemies
    vector <EnemyMeleeProp> enemy_melee_list;
    vector <EnemyRangedProp> enemy_ranged_list;
    //count time
    Uint64 currentTime;
    int old_choose,choose;

    //score
    unsigned int score;

    Word* score_word;
};


