#pragma once

#include "Player.h"

enum ENEMY_TYPE
{
    ENEMY_MELEE,
    ENEMY_RANGED,
    TOTAL_TYPE_ENEMY
};

const int ENEMY_SPEED = 5;
const int ENEMY_RELOAD = 20;

//spawn time
const int spawnTime[TOTAL_TYPE_ENEMY] = {100,150};


         /////////ENEMY
struct Enemy:Fighter
{
    //base stat
    const int nor_speed = ENEMY_SPEED;

    //func
    void drawEnemy(SDL_Renderer* renderer,const SDL_Point& camera);

    void getDmg(Fighter* t2);
};
        /////////////////////MELEE

struct EnemyMelee:Enemy
{
    EnemyMelee(SDL_Renderer* renderer);

    void update(SDL_Point& camera, Player* player, Map& gMap);
};


        /////////////SPAWN enemy
void spawnEnemyMelee(EnemyMelee* temp, vector <EnemyMelee*> &enemy, Entity* player, Map& gMap, SDL_Renderer* renderer);


