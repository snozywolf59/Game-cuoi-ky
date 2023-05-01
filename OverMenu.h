#pragma once

#include "Entity.h"
#include "Game.h"


class OverMenu
{
public:
    OverMenu(Resource* _res);

    int handle();

    void render();
private:
    unsigned int cnt;
    Resource* res;
};
