#include "Enemy.h"

//////////////////////////ENEMY////////////////////

void Enemy::drawEnemy(SDL_Renderer* renderer,const SDL_Point& camera)
{
    draw(NULL,renderer,camera);
}

/****************************************************/

void Enemy::getDmg(Fighter* t2)
{
    health -= t2->dmg;
    t2->health -=dmg;
    if (t2->health <= 0) t2->alive = false;
    if (health <= 0) alive = false;
}



        /////MELEE ENEMY
EnemyMelee::EnemyMelee(SDL_Renderer* renderer)
{
    //stat
    health = 5;
    dmg = 3;
    alive = true;

    //speed
    speed = ENEMY_SPEED;

    //reload
    reload = ENEMY_RELOAD;
}

/****************************************************/

void EnemyMelee::update(SDL_Point& camera, Player* player, Map& gMap)
{
    //chase player
        //set angle
    angle = getAngle(player);

    right = checkRight(gMap,speed);
    left = checkLeft(gMap,speed);
    up = checkUp(gMap,speed);
    down = checkDown(gMap,speed);

    //////hit player
    if (hitted(player))
    {
        left = 0, right = 0, down = 0, up = 0;

        if (reload == ENEMY_RELOAD)
        {
            reload = 0;

            player->health -= dmg;

            Mix_PlayChannel(SND_PLAYER_HITTED,player->isHitted,0);
        }
    }
    if (reload < ENEMY_RELOAD) reload++;

    double dx = speed*cos(angle), dy = speed*sin(angle);

    if (dx > 0 && right) x = x + dx;
    if (dx < 0 && left) x = x + dx;
    if (dy < 0 && up) y = y + dy;
    if (dy > 0 && down) y = y + dy;
}

/****************************************************/

            //spawn Enemy
void spawnEnemyMelee(EnemyMelee* temp, vector <EnemyMelee*> &enemy, Entity* player,Map& gMap, SDL_Renderer* renderer)
{
    EnemyMelee* newE = new EnemyMelee(renderer);
    //image loading and stat
    newE->texture = temp->texture;
    newE->w = temp->w;
    newE->h = temp->h;
    newE->angle = newE->getAngle(player);
    newE->alive = true;

    //spawn position
    int spawn_index = rand()%gMap.count_way;

    newE->x = (gMap.way[spawn_index] % MAP_SIZE) * BLOCK_SIZE;
    newE->y = (gMap.way[spawn_index]/MAP_SIZE) * BLOCK_SIZE;

    //push back to enemies
    enemy.push_back(newE);


    //clear
    newE = nullptr;

    delete newE;
}

/****************************************************/


