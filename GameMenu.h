#pragma once

#include "OverMenu.h"
#include "OptionMenu.h"

const string file_menu_mouse = "image/GameUI/GameMenu/Mouse.png";
const string FILE_MENU_IMAGE[] = {"image/GameUI/GameMenu/Play.png",
                                "image/GameUI/GameMenu/Option.png",
                                "image/GameUI/GameMenu/Quit.png"};


const string file_bg = "image/GameUI/GameMenu/bg.png";

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

    void menuOpTion();

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

    Mouse* mouse;

    //menu item
    OptionMenu* op;
    OverMenu* over;

    //flag for the mouse
    int choose = -1;
    int current = -1;

    //sound
    unsigned int volume;
    Mix_Chunk* beChosen;
    Mix_Music* bgMusic;

    TTF_Font* gFont;
    Entity* pad;

    //quit
    bool quit;
};
