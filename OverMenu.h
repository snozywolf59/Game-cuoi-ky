#pragma once

#include "Entity.h"
#include "Game.h"


class OverMenu
{
public:
    OverMenu(Resource* _res);

    int handle();

    string enter_name();

    void render_enter_name(const string& temp);

    void render();
private:
    unsigned int cnt;
    Resource* res;
};
