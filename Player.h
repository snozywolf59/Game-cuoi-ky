#pragma once

#include "Fighter&Bullet.h"


const string file_player = "image/player/player.png";
const string file_enemy_melee = "image/enemy/enemy_melee.png";
const string file_player_bullet = "image/player/bullet.png";
const string file_player_bullet_fire = "image/player/fire.png";

const int PLAYER_MAX_HP = 100;
const int PLAYER_RELOAD = 8;
const float PLAYER_SPEED = 0.2f;
const int PLAYER_DMG = 3;

const float R_player = 25.0f;

const float player_range = 1000.0f;

///////////////@@@##//PLAYER////////////////

struct Player:Entity
{
    Player(SDL_Renderer* renderer);

    int left = 0, right = 0, up = 0,down = 0;
    int health,dmg,reload,speed;
    bool alive = false;

    int now = 0;
    int atk;

    Bullet* bullet;
    Entity* pulse;
    Entity* bar;
    Entity* health_bar;

    //sound
    Mix_Chunk* attack;
    Mix_Chunk* isHitted;

    vector <FighterProp> p_bullets;

    void initStat();

    void initEngine();

    void initPos();

    void update(SDL_Point& camera, Mouse* mouse, Map* gMap);

    void updateAngle(Mouse* mouse);

    void updatePos(SDL_Point& camera,Map* gMap);

    void updateBullet(SDL_Point& camera, Mouse* mouse, Map* gMap);

    void updateEngine(SDL_Point& camera,Mouse* mouse, Map* gMap);

    void shoot(Mouse* mouse);

    void drawEngine(SDL_Point& camera);

    void drawPlayer(SDL_Point& camera);

    void drawHealthBar();
};

