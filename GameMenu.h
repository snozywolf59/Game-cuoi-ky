#pragma once

#include "Resource.h"
#include "OverMenu.h"
#include "OptionMenu.h"
#include "HighScore.h"

class GameMenu
{
public:
    GameMenu(Resource* _res);
    ~GameMenu();

    void handleMouse();

    void update();

    void menuDefault();

    void menuScores();

    void menuStart();

    void menuOpTion();

    void menuQuit();

    void menuOver();

    void render();

    void clearMenu();

    bool out();

private:

    SDL_Event e;

    Resource* res;

    //menu item
    Game* stage;
    OptionMenu* op;
    OverMenu* over;
    HighScoreMenu* scores;

    //flag for the mouse
    int choose = -1;
    int current = -1;

    //sound
    unsigned int volume;
    unsigned int snd;

    //quit
    bool quit;
};
