#include "Enemy.h"

int ti,tj;
float newX, newY, newX1, newY1;


EnemyProp::EnemyProp(ENEMY_TYPE _type, const float& x_, const float& y_,
                     const float& angle_)
{
    type = _type;
    x = x_, y = y_, angle = angle_, speed = E_SPEED;
    maxReload = E_RELOAD[type];
    maxFrame = E_MAX_FRAME[type], now = 0, reload = 0;
    health = E_HEALH[type];
    dmg = E_DMG[type];
    range = E_RANGE[type];
    resetMov(true);
    alive = true;
    R = R_enemy;
    smart = rand()%5;
}

void EnemyProp::resetMov(const bool& t)
{
    left = t, right = t, up = t, down = t;
    if (t == true) st = MOVE;
    else st = ATTACK;
}

void EnemyProp::shoot(Player* player, vector <BulletProp>& E_bullets)
{
    if (health > 0)
    {
        switch(type)
        {
            case ENEMY_MELEE:
                player->getDmg(dmg);
                break;
            case ENEMY_RANGED:
                BulletProp newBullet(NOR,x + 25 * cosf(angle), y + 25 * sinf(angle),
                                       angle ,BULLET_P_SPEED, 4);
                newBullet.R = E_RANGE[type];
                newBullet.dmg = dmg;
                E_bullets.push_back(newBullet);
                break;
        }
        resetMov(false);
        reload = 0;
    }
}


void EnemyProp::collisionBullet(Player* player)
{
    for (auto it = player->p_bullets.begin(); it != player->p_bullets.end();){
        if (health > 0 && getDistance(it->x,it->y,x,y) < R + it->R ){
                health -= player->dmg;
                if (it->type == NOR) it = player->p_bullets.erase(it);
                if (health <= 0){
                    now = 0;
                    maxFrame = maxFrameExplosion;
                    resetMov(false);
                    player->getMana(2);
                }
        }
        else ++it;
    }
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
            sum += normal(diff);
            cnt++;
        }
    }
    if (cnt > 0)
    {
        sum /= cnt;
    }
    return normal(sum);
}


void EnemyProp::avoidObs(Player* player, Map* gMap)
{
    Vec2f pos(x,y);
    Vec2f obs((ti + 0.5) * BLOCK_SIZE, (tj + 0.5) * BLOCK_SIZE);
    float oAngle = angle;
    angle = tangent1(pos, obs, 150);
    newX = x + speed * cosf(angle);
    newY = y + speed * sinf(angle);
    angle = tangent2(pos, obs, 150);
    newX1 = x + speed * cosf(angle);
    newY1 = y + speed * sinf(angle);
    if (getSqDis(newX1,newY1, player->x,player->y) < getSqDis(newX,newY, player->x,player->y)){
        x = newX1, y = newY1;
    }else{x = newX, y = newY;}
    angle = oAngle;
}


void EnemyProp::updateStat(Player* player, vector<BulletProp>& E_bullets)
{
    if (health <= 0 && now == maxFrame)
    {
        alive = false;
        return;
    }
    if (health > 0 && reload > maxReload/3) resetMov(true);
    float dis = getDistance(x,y,player->x,player->y);
    if ( dis < R_player + range){
        if (reload >= maxReload)
        {
            shoot(player,E_bullets);
        }
        resetMov(false);
    }
    collisionBullet(player);
    if (reload < maxReload) reload++;
}


void EnemyProp::updateEnemyPos(Player* player, vector<EnemyProp>& enemies, Map* gMap)
{
    Vec2f sep = separate(enemies);
    Vec2f d = normal(Vec2f(cosf(angle) + sep.x, sinf(angle) + sep.y));

    newX = x + speed * d.x, newY = y + speed * d.y;
    ti = newX / BLOCK_SIZE, tj = newY / BLOCK_SIZE;

    if (getDistance(newX, newY, (ti + 0.5) * BLOCK_SIZE, (tj + 0.5) * BLOCK_SIZE) >= gMap->getRadius(tj,ti) + 30){
        if ((left && d.x < 0) || (right && d.x > 0)) x = newX;
        if ((up && d.y < 0) || (down && d.y > 0)) y = newY;
    }else if (smart) avoidObs(player, gMap);

}

void EnemyProp::update(vector<EnemyProp>& enemies, Player* player, vector<BulletProp>& E_bullets,Map* gMap)
{
    updateStat(player,E_bullets);
    if (health > 0) {
        now = (now + 1)%maxFrame;
        updateAngle(player->x,player->y);
        if (reload > maxReload * 0.52f) updateEnemyPos(player,enemies,gMap);
    }
    else now++;
}


  //spawn Enemy
void spawnEnemyMelee(const Uint64& time, vector <EnemyProp>& enemy, Player* player,Map* gMap)
{
    int i , j;
    float spawnX, spawnY, angle, difficulty;
    do{
        int distance = 800 + (rand() % 201);
        angle = (rand()%360 - 180) * M_PI/180 ;
        difficulty = 1.5 * sqrtf(time);
        difficulty /= (sqrtf(time) + 300);
        spawnX = max(min(MAP_SIZE * 1.0f, player->x + distance * cosf(angle)),0.0f);
        spawnY = max(min(MAP_SIZE * 1.0f, player->y + distance * sinf(angle)),0.0f);
        i = spawnY / BLOCK_SIZE, j = spawnX/BLOCK_SIZE;
    }while(gMap->getRadius(i,j) > 0);
    EnemyProp x(ENEMY_MELEE,spawnX,spawnY,angle);
    x.health = E_HEALH[ENEMY_MELEE] * (1 + sqrtf(time) * 0.6f/350);
    x.speed = E_SPEED * (1 + difficulty);
    enemy.push_back(x);
}


void spawnEnemyRanged(const Uint64& time, vector<EnemyProp>& enemies, Player* player, Map* gMap)
{
    int i , j;
    float spawnX, spawnY, angle, difficulty;
    do{
        int distance = 800 + (rand() % 201);
        angle = (rand()%360 - 180) * M_PI/180 ;
        difficulty = 0.5 * sqrtf(time);
        difficulty /= (sqrtf(time) + 400);
        spawnX = max(min(MAP_SIZE * 1.0f, player->x + distance * cosf(angle)),0.0f);
        spawnY = max(min(MAP_SIZE * 1.0f, player->y + distance * sinf(angle)),0.0f);
        i = spawnY / BLOCK_SIZE, j = spawnX/BLOCK_SIZE;
    }while(gMap->getRadius(i,j) > 0);
    EnemyProp x(ENEMY_RANGED, spawnX, spawnY,angle);
    x.health = E_HEALH[ENEMY_RANGED] * (1 + sqrtf(time) * 0.6f/350);
    x.reload = E_RELOAD[ENEMY_RANGED] * (1 - difficulty);
    enemies.push_back(x);
}
