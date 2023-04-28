#pragma once

#include "Entity.h"
#include "Game.h"

const int SLIDER_W = 500;
const int SLIDER_H = 100;

const string file_game_over = "image/GameUI/GameOver/GameOver.png";
const string file_new_game = "image/GameUI/GameOver/NewGame.png";
const string file_menu_mouse = "image/GameUI/GameMenu/Mouse.png";
const string FILE_MENU_IMAGE[] = {"image/GameUI/GameMenu/Play.png",
                                "image/GameUI/GameMenu/Option.png",
                                "image/GameUI/GameMenu/Quit.png"};


const string file_bg = "image/GameUI/GameMenu/bg.png";


struct optionMenu
{
    Entity* backButton;
    Entity* opMouse;
    SDL_Rect fillRect;
    SDL_Renderer* renderer;
    bool out;

    const SDL_Rect vol_slider = {SCREEN_WIDTH/10, SCREEN_HEIGHT/3, SLIDER_W, SLIDER_H};

    optionMenu(Entity* mouse, SDL_Renderer* tRenderer);

    int handleAndUpdate(int& vol);

    void render();
};

struct OverMenu
{
    Button* MainMenu;
    Button* NewGame;
    Entity* GameOver;
    Mouse* mouse;
    Mix_Chunk* gameOverSound;
    SDL_Renderer* renderer;

    unsigned int cnt;

    OverMenu(SDL_Renderer* _renderer);

    int handle();

    void render();
};

class GameMenu
{
public:
    GameMenu(SDL_Renderer* gRenderer);
    ~GameMenu();

    //void init(bool fullScreen);

    void initMouse();

    void initButton();

    void initBackGround();

    void initSound();

    void initFontAndPad();

    void handleMouse();

    void update();

    void menuDefault();

    void menuStart();

    void menuScore();

    void menuQuit();

    void menuOver();

    void render();

    void clearMenu();

    bool out();

private:
    SDL_Renderer* renderer;

    //pointer to a stage
    Game* stage;
    SDL_Event e;


    //entity on the screen
    Button* button[TOTAL_BUTTON];

    Entity* bgImage;
    Entity* moon;

    Entity* mouse;

    //menu item
    optionMenu* op;
    OverMenu* over;

    //flag for the mouse
    int choose = -1;
    int current = -1;

    //sound
    int volume;
    Mix_Chunk* beChosen;
    Mix_Music* bgMusic;

    TTF_Font* gFont;
    Entity* pad;

    //quit
    bool quit;
};
