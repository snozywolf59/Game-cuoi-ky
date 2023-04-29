#include "Enemy.h"

void EnemyProp::resetMov(const bool& t)
{
    left = t, right = t, up = t, down = t;
    if (t == true) st = MOVE;
    else st = ATTACK;
}

Vec2f EnemyProp::separate(vector<EnemyProp>& enemies)
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



EnemyMeleeProp::EnemyMeleeProp(const float& x_, const float& y_,
                               const float& angle_, const float& _speed, const int& _maxReload, const int& _maxFrame)
{
    x = x_, y = y_, angle = angle_, speed = _speed * frameDelay, maxReload = _maxReload;
    maxFrame = _maxFrame, now = 0, reload = 0;
    health = ENEMY_HEALH[ENEMY_MELEE];
    dmg = ENEMY_DMG[ENEMY_MELEE];
    range = enemy_melee_range;
    resetMov(true);
    alive = true;
}

void EnemyMeleeProp::updateStat(Player* player)
{
    if (health <= 0 && now == maxFrame)
    {
        alive = false;
        return;
    }
    collisionBullet(player);
    collisionPlayer(player);
    if (reload < ENEMY_RELOAD) reload++;
}


void EnemyMeleeProp::updateEnemyPos(vector <EnemyMeleeProp>& enemies)
{
    float dx = cosf(angle);
    float dy = sinf(angle);
    if ((left && dx < 0) || (right && dx > 0)) x += speed * dx;
    if ((up && dy < 0) || (down && dy > 0)) y += speed * dy;
}

void EnemyProp::collisionBullet(Player* player)
{
    float maxR = R_bullet + R_enemy;
    for (auto it = player->p_bullets.begin(); it != player->p_bullets.end();){
        if (health > 0 && getDistance(it->x,it->y,x,y) < maxR ){
                health -= player->dmg;
                it = player->p_bullets.erase(it);
                if (health <= 0){
                    now = 0;
                    maxFrame = maxFrameExplosion;
                    resetMov(false);
                }
        }
        else{
                ++it;
        }
    }
}

void EnemyMeleeProp::collisionPlayer(Player* player)
{
    if (getDistance(player->x,player->y,x,y) < R_player + range){
        if (reload == ENEMY_RELOAD) {
                player->health -= dmg;
                reload = 0;
        }
        resetMov(false);
    } else if (reload > 60) resetMov(true);
}

void EnemyMeleeProp::update(vector <EnemyMeleeProp>& enemies,Player* player)
{
    updateStat(player);
    if (health > 0) {
        now = (now + 1)%maxFrame;
        updateAngle(player->x,player->y);
        updateEnemyPos(enemies);
    }
    else now++;
}

            //spawn Enemy
void spawnEnemyMelee(vector <EnemyMeleeProp>& enemy, Player* player,Map* gMap)
{
    int spawnX = 0;
    int spawnY = 0;
    EnemyMeleeProp x(spawnX,spawnY,getAngleGlobal(spawnX,spawnY,player->x,player->y));
    enemy.push_back(x);
}


EnemyRangedProp::EnemyRangedProp(const float& x_, const float& y_, const float& angle_, const float& _speed, const int& _maxReload, const int& _maxFrame)
{
    x = x_, y = y_, angle = angle_, speed = _speed * frameDelay, maxReload = _maxReload;
    maxFrame = _maxFrame, now = 0, reload = 0;
    health = ENEMY_HEALH[ENEMY_RANGED];
    dmg = ENEMY_DMG[ENEMY_RANGED];
    range = enemy_ranged_range;
    resetMov(true);
    alive = true;
}

void EnemyRangedProp::updateStat(Player* player)
{
    if (health <= 0 && now == maxFrame)
    {
        alive = false;
        return;
    }

    collisionBullet(player);
}

void EnemyRangedProp::updateBullet(Player* player){
    if (getDistance(player->x,player->y,x,y) < R_player + range){
        if (reload == ENEMY_RELOAD) {
                shoot(player);
                reload = 0;
        }
        resetMov(false);
    } else if (reload > 60) resetMov(true);
    float maxR = R_bullet + R_player;
    for (auto prop = E_bullets.begin(); prop != E_bullets.end();)
    {
        prop->updatePos();
        cout << prop->x << ' ' << prop-> y << ' ' << player->x <<' ' << player->y << endl;
        prop->now = (prop->now + 1)%prop->maxFrame;
        if (prop->s > range)
        {
            prop = E_bullets.erase(prop);
            continue;
        }
        if (getDistance(player->x,player->y,prop->x,prop->y) < maxR)
        {
            player->health -= dmg;
            prop = E_bullets.erase(prop);
            continue;
        }
        ++prop;
    }
    if (reload < ENEMY_RELOAD) reload++;
}

void EnemyRangedProp::shoot(Player* player)
{
    FighterProp newBullet(x + 25 * cosf(angle), y + 25 * sinf(angle) , angle ,BULLET_P_SPEED, 4*5);
    E_bullets.push_back(newBullet);
    reload = 0;
}

void EnemyRangedProp::updateEnemyPos(vector<EnemyRangedProp>& enemies)
{
    float dx = cosf(angle);
    float dy = sinf(angle);
    if ((left && dx < 0) || (right && dx > 0)) x += speed * dx;
    if ((up && dy < 0) || (down && dy > 0)) y += speed * dy;
}

void EnemyRangedProp::update(vector<EnemyRangedProp>& enemies, Player* player)
{
    updateStat(player);
    if (health > 0) {
        now = (now + 1)%maxFrame;
        updateAngle(player->x,player->y);
        updateEnemyPos(enemies);
    }
    else now++;

    updateBullet(player);
}

void spawnEnemyRanged(vector<EnemyRangedProp>& enemies, Player* player, Map* gMap)
{
    int spawnX = 0;
    int spawnY = 0;
    EnemyRangedProp x(spawnX,spawnY,getAngleGlobal(spawnX,spawnY,player->x,player->y));
    enemies.push_back(x);
}
