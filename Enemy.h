#pragma once

#include "Player.h"
const int maxFrameEnemyMelee = 6 * DELAY;
const int maxFrameEnemyRanged = 6 * DELAY;
const int maxFrameExplosion = 8 * DELAY;
const int ENEMY_RELOAD = 2 * FPS;
const float R_enemy = 30.0f;

const float ENEMY_SPEED = 0.2;
//spawn time
enum ENEMY_TYPE
{
    ENEMY_MELEE,
    ENEMY_RANGED,
    TOTAL_TYPE_ENEMY
};
const int enemy_melee_spawntime = FPS;
const int enemy_ranged_spawntime = 2 * FPS;

const int enemy_melee_range = 10;
const int enemy_ranged_range = 800;

const int ENEMY_HEALH[TOTAL_TYPE_ENEMY] = {6,3};
const int ENEMY_DMG[TOTAL_TYPE_ENEMY] = {3,2};

enum ENEMY_STAT
{
    MOVE,
    ATTACK
};

struct EnemyProp:FighterProp
{
    int reload, maxReload, health, dmg, st, range;
    bool left, right, up, down;
    bool alive;

    void resetMov(const bool& t);

    void collisionBullet(Player* player);

    Vec2f separate(vector <EnemyProp>& enemies);
};

struct EnemyMeleeProp:EnemyProp
{
    EnemyMeleeProp(const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = ENEMY_SPEED, const int& _maxReload = ENEMY_RELOAD,
                const int& _maxFrame = maxFrameEnemyMelee);

    void updateStat(Player* player);

    void collisionPlayer(Player* player);

    void updateEnemyPos(vector <EnemyMeleeProp>& enemies);

    void update(vector <EnemyMeleeProp>& enemies,Player* player);
};

struct EnemyRangedProp:EnemyProp
{
    vector <FighterProp> E_bullets;

    EnemyRangedProp(const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = ENEMY_SPEED, const int& _maxReload = ENEMY_RELOAD,
                const int& _maxFrame = maxFrameEnemyRanged);

    void updateStat(Player* player);

    void updateBullet(Player* player);

    void shoot(Player* player);

    void updateEnemyPos(vector <EnemyRangedProp>& enemies);

    void update(vector <EnemyRangedProp>& enemies,Player* player);
};


        /////////////SPAWN enemy
void spawnEnemyMelee(vector <EnemyMeleeProp>& enemies, Player* player,Map* gMap);
void spawnEnemyRanged(vector <EnemyRangedProp>& enemies, Player* player,Map* gMap);


