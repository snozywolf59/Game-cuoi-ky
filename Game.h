#pragma once

#include "Enemy.h"

#define NORMAL 1000

enum BUTTON_MENU_TYPE
{
    DEFAULT = -1,
    START,
    SCORE,
    QUIT,
    TOTAL_BUTTON
};


enum ING_BUTTON
{
    ING_PAUSE,
    ING_RESUME,
    ING_MENU,
    ING_QUIT,
    ING_TOTAL
};
const string file_ing_mouse = "image/Game/InGame/Mouse.png";

const string FILE_ING_BUT[] = { "image/Game/InGame/Pause.png",
                                "image/Game/InGame/Resume.png",
                                "image/Game/InGame/Menu.png",
                                "image/Game/GameMenu/Quit.png"};

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

    void drawButtons();

    void drawEnemy();

    void drawPlayer();

    void drawMap();

    void drawPoint();

    void drawMouse();

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
    Map* gMap;
    SDL_Point camera;
    Mouse* mouse;

    //enemies
    Entity* enemy_melee;
    vector <EnemyMeleeProp> enemy_list;

    //explosion animation
    Entity* explosion;

    //count time
    Uint64 currentTime;

    //score
    int score;

    //sound
    Mix_Chunk* enemy_die;
    Mix_Music* bgMusic;

    //ing button
    Button* Ing_Button[ING_TOTAL];

    //font
    Word* score_word;
};


