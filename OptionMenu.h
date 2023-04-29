#pragma once

#include "Entity.h"
#include "Game.h"

const string file_back_button = "image/GameUI/GameOption/Back.png";
const string file_music_buttonOn = "image/GameUI/GameOption/MusicOn.png";
const string file_music_buttonOff = "image/GameUI/GameOption/MusicOff.png";
const string file_music_slider = "image/GameUI/GameOption/Bar.png";
const string file_yellow_bar = "image/GameUI/GameOption/Yellow.png";

struct OptionMenu
{
    Button* backButton;
    Button* musicOn;
    Button* musicOff;
    Entity* music_slider;
    Entity* yellow_bar;
    Entity* opMouse;
    SDL_Renderer* renderer;
    TTF_Font* font;

    OptionMenu(TTF_Font* _font,Entity* mouse, SDL_Renderer* tRenderer);

    int handleAndUpdate(unsigned int& vol);

    void doVol(unsigned int& vol, SDL_Event* e);

    void render(const unsigned int& vol);
};

