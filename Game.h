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

    unsigned int getScore();

    int handleEvent();

    int doButton();

    void doKeyBoard();

    void doMouse();

    void updateEBullets();

    void updateEnemy();

    void updateItems();

    void update();

    void drawButtons();

    void drawEnemy();

    void drawEBullets();

    void drawPlayer();

    void drawMap();

    void drawItems();

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

    vector <Item> items;

    //enemies
    vector <EnemyProp> enemy_list;
    vector <FighterProp> E_bullets;
    //count time
    Uint32 currentTime;
    int old_choose,choose;

    //score
    unsigned int sub_score;
    unsigned int score;

    Word* score_word;
};


