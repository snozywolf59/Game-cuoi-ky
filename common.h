#ifndef COMMON__H
#define COMMON__H

#include<fstream>
#include<vector>
#include<ctime>
#include<iostream>
#include<cmath>
#include<sstream>


#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

//based define
#define SCREEN_WIDTH 1008
#define SCREEN_HEIGHT 648
#define TITLE "Slay Zombie"


//control frames per second (FPS)
#define FPS 50
#define frameDelay 1000/FPS

//PI
#define PI 3.14159265358979323846

using namespace std;

//screen handle
//basic
void logSDLError(ostream& os,const string &msg, bool fatal);

//**************************IMG**********************//
//file for image

enum IMAGE_ENTITY
{
    IMG_MOUSE_ING,
    IMG_PLAYER,
    IMG_BULLET,
    IMG_ENEMY_MELEE,
    IMG_MOUSE_MENU,
    TOTAL_IMAGE
};


const string FILE_ENTITY_IMAGE[] =
{
    "image/map/mouse.png",
    "image/player/player.png",
    "image/player/bullet.png",
    "image/enemy/enemy_melee.png"
};

//image for menu


const string FILE_MENU_IMAGE[] =
{
    "image/Game/GameMenu/Play.png",
    "image/Game/GameMenu/Option.png",
    "image/Game/GameMenu/Quit.png",
    "image/Game/GameMenu/Colored/start.png"
};

//color
const Uint8 RGB[] = { 203, 203, 203, // Gray
                  254, 254,  31, // Yellow
                    0, 255, 255, // Cyan
                    0, 254,  30, // Green
                  255,  16, 253, // Magenta
                  253,   3,   2, // Red
                   18,  14, 252, // Blue
                    0,   0,   0,  // Black
                    255, 255, 255, //White
                    200, 170, 65 //Background
};

enum COLOR
{
    GRAY,
    YELLOW,
    CYAN,
    GREEN,
    MAGENTA,
    RED,
    BLUE,
    BLACK,
    WHITE,
    BACKGROUND,
    TOTAL_COLOR
};

    //map file

const char file_bg[] = {"image/Game/bgImage-min.png"};
const char txt_map[] = {"map/map.txt"};

    //ingame button
const string file_ing_but[] = {
    "image/Game/InGame/Pause.png",
    "image/Game/InGame/Resume.png",
    "image/Game/InGame/Menu.png",
    "image/Game/GameMenu/Quit.png"
};



//**************************TTF***********************//
const char gameFont[] = {"font/lazy.ttf"};


string convertIntToString(const int& x);

//*************************MIXER*********************//

enum SOUND
{
    SND_PLAYER_HITTED,
    SND_PLAYER_SHOOT,
	SND_ENEMY_DIE,
	SND_GAME_OVER,
	SND_MAX
};

const char snd_menu_beChosen[] = {"sound/menu/beChosen.wav"};

const char snd_menu_bgMusic[] = {"sound/menu/bgMusic.wav"};

const char snd_game_bgMusic[] = {"sound/game/bgMusic_fixed.wav"};

const char snd_player_shoot[] = {"sound/player/player_shoot_fixed.wav"};

const char snd_player_hitted[] = { "sound/player/player_is_hitted_fixed.wav" };

const char snd_enemy_die[] = {"sound/enemies/enemy_die_fixed.wav"};

const char snd_game_over[] = {"sound/game/game_over.wav"};



#endif // COMMON__H
