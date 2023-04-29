#pragma once

#include "Entity.h"
#include "Game.h"

const int SLIDER_W = 500;
const int SLIDER_H = 100;

const string file_back_button = "image/GameUI/GameOption/Back.png";
const string file_music_buttonOn = "image/GameUI/GameOption/MusicOn.png";
const string file_music_buttonOff = "image/GameUI/GameOption/MusicOff.png";

struct OptionMenu
{
    Button* backButton;
    Button* musicOn;
    Button* musicOff;
    Entity* opMouse;
    SDL_Rect fillRect;
    SDL_Renderer* renderer;
    TTF_Font* font;

    const SDL_Rect vol_slider = {SCREEN_WIDTH/10, SCREEN_HEIGHT/3, SLIDER_W, SLIDER_H};

    OptionMenu(TTF_Font* _font,Entity* mouse, SDL_Renderer* tRenderer);

    int handleAndUpdate(unsigned int& vol);

    void render(const unsigned int& vol);
};

