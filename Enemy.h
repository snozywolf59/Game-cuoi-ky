#pragma once

#include "Player.h"

//spawn time
enum ENEMY_TYPE
{
    ENEMY_MELEE,
    ENEMY_RANGED
};

enum ENEMY_STAT
{
    MOVE,
    ATTACK
};

const int maxFrameExplosion = 8 * DELAY;
const float E_RELOAD[] = {1.2 * FPS, 2 * FPS};
const float R_enemy = 30.0f;

const float E_SPEED = 0.2f * frameDelay;

const int E_MAX_FRAME[] = {6 * DELAY, 6 * DELAY};
const int E_SPAWN_T[] = {FPS, 2 * FPS};
const int E_RANGE[] = {25, 750};
const int E_HEALH[] = {6,3};
const int E_DMG[] = {3,2};


struct EnemyProp:FighterProp
{
    int health, st, range;
    float reload, maxReload;
    bool left, right, up, down;
    ENEMY_TYPE type;
    bool alive;
    bool smart;

    EnemyProp(ENEMY_TYPE _type, const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0);

    void resetMov(const bool& t);

    void shoot(Player* player, vector <BulletProp>& E_bullets);

    void collisionBullet(Player* player);

    //each enemy will not stack up others (may be not xD)
    Vec2f separate(vector <EnemyProp>& enemies);

    //avoid obstacles (in this case: some planets)
    void avoidObs(Player* player, Map* gMap);

    void updateStat(Player* player,  vector<BulletProp>& E_bullets);

    void updateEnemyPos(Player* player, vector <EnemyProp>& enemies, Map* gMap);

    void update(vector <EnemyProp>& enemies,Player* player, vector<BulletProp>& E_bullets,Map* gMap) ;
};

        /////////////SPAWN enemy
void spawnEnemyMelee(const Uint64& time, vector <EnemyProp>& enemies, Player* player,Map* gMap);
void spawnEnemyRanged(const Uint64& time, vector <EnemyProp>& enemies, Player* player,Map* gMap);


