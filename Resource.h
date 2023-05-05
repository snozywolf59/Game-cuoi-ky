#pragma once

#include "Entity.h"
#include "Button.h"
#include "Mouse.h"
#include "Word.h"
#include "Item.h"

enum BUTTON_MENU_TYPE
{
    DEFAULT = -1,
    START,
    OPTION,
    HIGHSCORE,
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


//MENU
const string file_menu_mouse = "image/GameUI/GameMenu/Mouse.png";

const string FILE_MENU_IMAGE[] = {
    "image/GameUI/GameMenu/Play.png",
    "image/GameUI/GameMenu/Option.png",
    "image/GameUI/GameMenu/HighScore.png",
    "image/GameUI/GameMenu/Quit.png"
};


const string file_bg = "image/GameUI/GameMenu/bg.png";


//GAME
const string file_ing_mouse = "image/GameUI/InGame/Mouse.png";

const string FILE_ING_BUT[] = {
    "image/GameUI/InGame/Pause.png",
    "image/GameUI/InGame/Resume.png",
    "image/GameUI/InGame/Menu.png",
    "image/GameUI/GameMenu/Quit.png"
};

const string file_explosion = "image/enemy/explosion.png";
const string file_enemy_bullet = "image/enemy/bullet.png";
const string file_enemy_melee = "image/Enemy/enemy_melee.png";
const string file_enemy_ranged = "image/Enemy/enemy_ranged.png";

const string file_game_over = "image/GameUI/GameOver/GameOver.png";
const string file_new_game = "image/GameUI/GameOver/NewGame.png";

const string file_back_button = "image/GameUI/GameOption/Back.png";
const string file_music_buttonOn = "image/GameUI/GameOption/MusicOn.png";
const string file_music_buttonOff = "image/GameUI/GameOption/MusicOff.png";
const string file_sound_buttOn = "image/GameUI/GameOption/soundOn.png";
const string file_sound_buttOff = "image/GameUI/GameOption/soundOff.png";
const string file_slider = "image/GameUI/GameOption/Bar.png";
const string file_yellow_bar = "image/GameUI/GameOption/Yellow.png";
const string file_pad = "image/GameUI/InGame/Pad.png";
const string file_board = "image/GameUI/Board.png";
const string file_score_img = "image/GameUI/Score1.png";

const string file_game_font = "font/Zector.ttf";
const int font_size = 50;

const string file_ITEMS[] = {
    "image/Items/Point.png",
    "image/Items/Health.png",
    "image/Items/Shield.png"
};

struct Resource
{
    SDL_Renderer* renderer;

    //button
    Button* But_Menu[TOTAL_BUTTON];
    Button* But_InG[ING_TOTAL];
    Button* But_NewGame;
    Button* But_MainMenu;
    Button* But_Back;
    Button* But_MusicOn;
    Button* But_MusicOff;
    Button* But_SoundOn;
    Button* But_SoundOff;

    //mouse
    Mouse* Menu_Mouse;
    Mouse* InGame_Mouse;


    //entity
    Entity* MenuBG;
    Entity* pad;
    Entity* board;
    Entity* score;

    Entity* slider;
    Entity* yellow_bar;

    Entity* game_over;

    Entity* enemy_melee;
    Entity* enemy_ranged;
    Entity* e_bullet;
    Entity* explosion;

    Entity* Items[TOTAL_ITEMS];

    //font
    TTF_Font* font;

    //WORD
    Word* congratulate;
    Word* enter_name;
    Word* too_long;

    //music
    Mix_Music* Menu_bgMusic;
    Mix_Music* InG_Music;

    //chunk
    Mix_Chunk* enemy_die;
    Mix_Chunk* But_beChosen;

    //
    Resource(SDL_Renderer* _renderer);
};
