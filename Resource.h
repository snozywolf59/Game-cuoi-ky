#pragma once

#include "Entity.h"
#include "Button.h"
#include "Mouse.h"

//MENU
const string file_menu_mouse = "image/GameUI/GameMenu/Mouse.png";

const string FILE_MENU_IMAGE[] = {"image/GameUI/GameMenu/Play.png",
                                "image/GameUI/GameMenu/Option.png",
                                "image/GameUI/GameMenu/Quit.png"};


const string file_bg = "image/GameUI/GameMenu/bg.png";


//GAME
const string file_ing_mouse = "image/GameUI/InGame/Mouse.png";

const string FILE_ING_BUT[] = { "image/GameUI/InGame/Pause.png",
                                "image/GameUI/InGame/Resume.png",
                                "image/GameUI/InGame/Menu.png",
                                "image/GameUI/GameMenu/Quit.png"};

const string file_explosion = "image/enemy/explosion.png";
const string file_enemy_bullet = "image/enemy/bullet.png";
const string file_enemy_melee = "image/Enemy/enemy_melee.png";
const string file_enemy_ranged = "image/Enemy/enemy_ranged.png";


enum BUTTON_MENU_TYPE
{
    DEFAULT = -1,
    START,
    OPTION,
    QUIT,
    TOTAL_BUTTON
};


enum ING_BUTTON
{
    ING_PAUSE,
    ING_RESUME,
    ING_MENU,
    ING_QUIT,
    ING_TOTAL
};

struct Resource
{
    SDL_Renderer* renderer;

    //common
    Button* But_Menu[TOTAL_BUTTON];

    Button* But_NewGame;

    Mouse* Menu_Mouse;

    Entity* MenuBG;
    Entity* pad;


    TTF_Font* font;

    Mix_Chunk* But_beChosen;
    Mix_Music* Menu_bgMusic;

    //stage
    Button* But_InG[ING_TOTAL];
    Mouse* InGame_Mouse;
    Mix_Chunk* enemy_die;
    Mix_Music* InG_Music;
    Entity* enemy_melee;
    Entity* enemy_ranged;
    Entity* e_bullet;
    Entity* explosion;

    Resource(SDL_Renderer* _renderer);
};
