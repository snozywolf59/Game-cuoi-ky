#include "Enemy.h"


EnemyMeleeProp::EnemyMeleeProp(const float& x_, const float& y_,
                               const float& angle_, const float& _speed, const int& _maxReload, const int& _maxFrame)
{
    x = x_, y = y_, angle = angle_, speed = _speed * frameDelay, maxReload = _maxReload;
    maxFrame = _maxFrame, now = 0, reload = 0;
    dmg = ENEMY_DMG[ENEMY_MELEE];
    left = true, right = true, up = true, down = true;
    alive = true;
}
void EnemyMeleeProp::resetMov(const bool& t)
{
    left = t, right = t, up = t, down = t;
}

void EnemyMeleeProp::updateEnemyPos(vector <EnemyMeleeProp>& enemies)
{
    Vec2f temp = separate(enemies);
    float dx = temp.x;
    float dy = temp.y;
    if ((left && dx < 0) || (right && dx > 0)) x += speed * dx;
    if ((up && dy < 0) || (down && dy > 0)) y += speed * dy;
}

void EnemyMeleeProp::update(vector <EnemyMeleeProp>& enemies,Player* player)
{
    updateStat(player);
    updateAngle(player->x,player->y);
    updateEnemyPos(enemies);
    now = (now + 1)%maxFrame;
}

void EnemyMeleeProp::updateStat(Player* player)
{
    float maxR = R_bullet + R_enemy;
    for (auto it = player->p_bullets.begin(); it != player->p_bullets.end();)
    {
        if (getDistance(it->x,it->y,x,y) < maxR )
        {
            health -= player->dmg;
            it = player->p_bullets.erase(it);
        }
        else{
                ++it;
        }
    }
    if (getDistance(player->x,player->y,x,y) < R_bullet + R_player)
    {
        if (reload == ENEMY_RELOAD) {
                player->health -= dmg;
                reload = 0;
        }
        resetMov(false);
    } else if (reload > 20) resetMov(true);

    if (reload < ENEMY_RELOAD) reload++;
}

Vec2f EnemyMeleeProp::separate(const vector<EnemyMeleeProp>& enemies)
{
    Vec2f sum(0.0f, 0.0f);
    int cnt = 0;
    float maxR = 50;
    Vec2f pos(x,y);
    for (const auto& t : enemies)
    {
        Vec2f other(t.x,t.y);
        if (&t != this && distance(pos, other) < maxR)
        {
            Vec2f diff = pos - other;
            sum += diff;
            cnt++;
        }
    }
    if (cnt > 0)
    {
        sum /= (float)cnt;
    }
    return normalize(sum);
}


            //spawn Enemy
void spawnEnemyMelee(vector <EnemyMeleeProp>& enemy, Player* player,Map* gMap)
{
    int spawnX = 0;
    int spawnY = 0;
    EnemyMeleeProp x(spawnX,spawnY,getAngleGlobal(spawnX,spawnY,player->x,player->y));
    enemy.push_back(x);
}


/****************************************************/


