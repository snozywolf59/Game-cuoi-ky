#include "Button.h"

////////////////////////////////////BUTTON////////////////////////
Button::Button(SDL_Renderer* _renderer, const string& path)
{
    renderer = _renderer;
    loadEntity(path);
}



bool Button::beChosen(const int& _x,const int& _y, const int& _w, const int& _h)
{
    if ( _x >= x && _x <= x + _w)
        if (_y >= y && _y <= y + _h)
        {
            now = 1;
            scale = 1.1;
            return true;
        }

    now = 0;
    scale = 1;
    return false;
}


void Button::drawButton(const int& _x,const int& _y, const int& _w, const int& _h)
{
    this->x = _x;
    this->y = _y;

    SDL_Rect selected = {now * w/2, 0, w/2, h};

    draw(&selected,_x,_y,_w,_h,0);
}

