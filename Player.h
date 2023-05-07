#pragma once

#include "Fighter&Bullet.h"
#include "Resource.h"


const string file_player = "image/Player/player.png";
const string file_player_bullet = "image/Player/bullet.png";
const string file_player_bullet_fire = "image/Player/fire.png";
const string file_bar = "image/Player/bar.png";
const string file_bar_health = "image/Player/red.png";
const string file_bar_mana = "image/Player/blue.png";
const string file_player_pulse = "image/Player/pulse.png";
const string file_player_shield = "image/Player/shield.png";

const string file_skill1 = "image/Player/ThunderExplos.png";
const string file_skill2 = "image/Player/UltimateBall.png";

const int PLAYER_MAX_HP = 50;
const int PLAYER_MAX_MANA = 300;
const int PLAYER_RELOAD = 12;
const float PLAYER_SPEED = 0.2f * frameDelay;
const int PLAYER_DMG = 3;
const int SHIELD_TIME = 5 * FPS;
const int Speed_TIME = 10 * FPS;
const float R_player = 25.0f;

const float player_range = 1000.0f;

/////////////////PLAYER////////////////

struct Player:Entity
{
    Player(SDL_Renderer* renderer);

    int right, left, down, up;
    int health, maxH, mana, maxM, dmg, bDmg, reload, maxReload, bReload;

    int shield_time = 0, s_boost = 0;
    float speed, bSpeed;
    bool alive = false;

    int now;
    int atk, skl1, skl2;

    Entity* bullet;
    Entity* skill1;
    Entity* skill2;
    Entity* fire;
    Entity* pulse;
    Entity* bar;
    Entity* health_bar;
    Entity* mana_bar;
    Entity* shield;

    //sound
    Mix_Chunk* attack;
    Mix_Chunk* isHitted;

    vector <BulletProp> p_bullets;

    void initStat();

    void initEngine();

    void initPos();

    void getDmg(const int& hurt);

    void getItem(Item& it, unsigned int& score);

    void getMana(const int& bonus = 1);

    void update(Vec2f& camera, Mouse* mouse, Map* gMap, const Uint32& time);

    void updateAngle(Mouse* mouse);

    void updatePos(Vec2f& camera, Map* gMap);

    void updateBullet(Vec2f& camera, Mouse* mouse, Map* gMap);

    void updateEngine(Vec2f& camera,Mouse* mouse, Map* gMap, const Uint32& time);

    void shoot(Mouse* mouse);

    void castSkill_1();
    void castSkill_2();

    void drawBullet(const Vec2f& camera);

    void drawEngine(Vec2f& camera);

    void drawPlayer(Vec2f& camera);

    void drawHealthBar();
};

