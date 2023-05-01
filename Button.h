#pragma once

#include "Entity.h"


#define BUTTON_HEIGHT 90
#define BUTTON_WIDTH 270
#define ING_BUT_W 80
#define ING_BUT_H 80

struct Button:Entity
{
    const float default_scale = 1;

    //SDL_Rect selected;
    int now = 0;

    Button(SDL_Renderer* _renderer, const string& path);

    bool beChosen(const int& _x,const int& _y, const int& _w, const int& _h);

    void drawButton(const int& _x,const int& _y, const int& _w, const int& _h);
};
