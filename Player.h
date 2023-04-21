#pragma once

#include "Entity.h"

#define PLAYER_DELAY 5

const int PLAYER_MAX_HP = 20;
const int PLAYER_RELOAD = 8;
const int PLAYER_SPEED = 5;
const int PLAYER_DMG = 3;

struct BulletProp
{
    float x, y, angle;
    int speed;
    BulletProp();
    BulletProp(const float& x_,const float& y_,const float& angle_,const int& _speed);
};

///////////////@@@##//PLAYER////////////////

struct Player:Fighter
{
    Player(SDL_Renderer* renderer);

    //current stat
    int atk;

    Entity* bullet;

    //sound
    Mix_Chunk* attack;
    Mix_Chunk* isHitted;

    vector <BulletProp> p_bullets;

    void update(SDL_Point& camera, Mouse* mouse, Map& gMap);

    void updateAngle(Mouse* mouse);

    void updatePos(SDL_Point& camera,Map& gMap);

    void updateBullet(SDL_Point& camera, Mouse* mouse, Map& gMap);

    void shoot(Mouse* mouse);

    void drawBullet(SDL_Renderer* renderer,SDL_Point& camera,float scale = 1);

    void drawPlayer(SDL_Renderer* renderer,SDL_Point& camera);
};

