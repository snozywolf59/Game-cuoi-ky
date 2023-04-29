#pragma once

#include "Fighter&Bullet.h"


const string file_player = "image/Player/player.png";
const string file_player_bullet = "image/Player/bullet.png";
const string file_player_bullet_fire = "image/Player/fire.png";
const string file_bar = "image/Player/bar.png";
const string file_bar_health = "image/Player/red.png";
const string file_player_pulse = "image/Player/pulse.png";

const int PLAYER_MAX_HP = 50;
const int PLAYER_RELOAD = 12;
const float PLAYER_SPEED = 0.2f;
const int PLAYER_DMG = 3;

const float R_player = 25.0f;

const float player_range = 1000.0f;

/////////////////PLAYER////////////////

struct Player:Entity
{
    Player(SDL_Renderer* renderer);

    int left = 0, right = 0, up = 0,down = 0;
    int health,dmg,reload;
    float speed;
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

    void update(Vec2f& camera, Mouse* mouse, Map* gMap);

    void updateAngle(Mouse* mouse);

    void updatePos(Vec2f& camera,Map* gMap);

    void updateBullet(Vec2f& camera, Mouse* mouse, Map* gMap);

    void updateEngine(Vec2f& camera,Mouse* mouse, Map* gMap);

    void shoot(Mouse* mouse);

    void drawEngine(Vec2f& camera);

    void drawPlayer(Vec2f& camera);

    void drawHealthBar();
};

