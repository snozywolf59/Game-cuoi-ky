#pragma once

#include "Entity.h"
#include "Game.h"

const int SLIDER_W = 500;
const int SLIDER_H = 100;

struct optionMenu
{
    Entity backButton;
    Entity* opMouse;
    SDL_Rect fillRect;
    SDL_Renderer* renderer;
    bool out;

    const SDL_Rect vol_slider = {SCREEN_WIDTH/10, SCREEN_HEIGHT/3, SLIDER_W, SLIDER_H};

    optionMenu(Entity* mouse, SDL_Renderer* tRenderer);

    int handleAndUpdate(int& vol);

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

    void handleMouse();

    void update();

    void menuDefault();

    void menuStart();

    void menuOption();

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
    Button button[TOTAL_BUTTON];

    Entity bgImage;

    Entity mouse;

    //menu item
    optionMenu* op;

    //flag for the mouse
    int choose = -1;
    int current = -1;

    //sound
    int volume;
    Mix_Chunk* beChosen;
    Mix_Music* bgMusic;

    //quit
    bool quit;
};
