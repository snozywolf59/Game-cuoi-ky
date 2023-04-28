#pragma once

#include "Player.h"

const string file_enemy_melee = "image/Enemy/enemy_melee.png";

const int maxFrameEnemyMelee = 6 * DELAY;
const int maxFrameEnemyRanged = DELAY;
const int maxFrameExplosion = 8 * DELAY;
const int ENEMY_RELOAD = 2 * FPS;
const int ENEMY_MELEE_BLOCK_SIZE = 51;
const float R_enemy = 30.0f;

const float ENEMY_SPEED = 0.2;
//spawn time
enum ENEMY_TYPE
{
    ENEMY_MELEE,
    ENEMY_RANGED,
    TOTAL_TYPE_ENEMY
};
const int spawnTime[TOTAL_TYPE_ENEMY] = {1 * FPS, 2 * FPS};
const int ENEMY_HEALH[TOTAL_TYPE_ENEMY] = {8,5};
const int ENEMY_DMG[TOTAL_TYPE_ENEMY] = {3,2};

struct EnemyProp:FighterProp
{
    int reload, maxReload, health, dmg;
    bool left, right, up, down;
    bool alive;

    void resetMov(const bool& t);

    void collisionBullet(Player* player);

    void collisionPlayer(Player* player);

    Vec2f separate(vector <EnemyProp>& enemies);
};

struct EnemyMeleeProp:EnemyProp
{
    EnemyMeleeProp(const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = ENEMY_SPEED, const int& _maxReload = ENEMY_RELOAD,
                const int& _maxFrame = maxFrameEnemyMelee);

    void updateStat(Player* player);

    void updateEnemyPos(vector <EnemyMeleeProp>& enemies);

    void update(vector <EnemyMeleeProp>& enemies,Player* player);
};

struct EnemyRangedProp:EnemyProp
{

    EnemyRangedProp(const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = ENEMY_SPEED, const int& _maxReload = ENEMY_RELOAD,
                const int& _maxFrame = maxFrameEnemyRanged);

    void updateStat(Player* player);

    void updateEnemyPos(vector <EnemyRangedProp>& enemies);

    void update(vector <EnemyRangedProp>& enemies,Player* player);
};


        /////////////SPAWN enemy
void spawnEnemyMelee(vector <EnemyMeleeProp>& enemies, Player* player,Map* gMap);


