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

const string txt_map= "map/map.txt";
//**************************TTF***********************//
const string gameFont = "font/lazy.ttf";


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
