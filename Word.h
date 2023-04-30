#pragma once

#include "Entity.h"

struct Word:Entity
{
    TTF_Font* font;

    Entity* pad;

    SDL_Color color;

    Word(const int& _x, const int& _y, SDL_Renderer* renderer, TTF_Font* gFont, Entity* gPad);

    void loadFromRenderedText (const string& textureText, SDL_Color textColor, SDL_Renderer* renderer);

    void drawWord();

    void drawWord(const int& _x,const int& _y, const int& _w, const int& _h);
};



