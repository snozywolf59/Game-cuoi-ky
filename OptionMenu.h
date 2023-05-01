#pragma once

#include "Entity.h"
#include "Game.h"

class OptionMenu
{
public:
    OptionMenu(Resource* _res);

    int handleAndUpdate(unsigned int& vol, unsigned int& snd);

    void doVol(unsigned int& vol, SDL_Event* e);

    void doSnd(unsigned int& snd, SDL_Event* e);

    void render(const unsigned int& vol, const unsigned int& snd);

private:
    Resource* res;
};

