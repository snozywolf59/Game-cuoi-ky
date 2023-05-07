#include "Player.h"

///////////////////////////PLAYER/////////////////////////

SDL_Rect t;

Player::Player(SDL_Renderer* trenderer)
{
    renderer = trenderer;

    initEngine();
    initStat();
    initPos();
}

void Player::initEngine()
{
    loadEntity(file_player);

    bar = new Entity(renderer,file_bar);
    health_bar = new Entity(renderer, file_bar_health);
    mana_bar = new Entity(renderer, file_bar_mana);

    bullet = new Entity(renderer,file_player_bullet);
    fire = new Entity(renderer, file_player_bullet_fire);
    shield = new Entity(renderer, file_player_shield);
    pulse = new Entity(renderer,file_player_pulse);
    pulse->w = 28;
    pulse->h = 14;
    skill1 = new Entity(renderer, file_skill1);
    skill2 = new Entity(renderer, file_skill2);

    attack = Mix_LoadWAV(snd_player_shoot);
    isHitted = Mix_LoadWAV(snd_player_hitted);
    ulti = Mix_LoadWAV(snd_player_ulti);
}


void Player::initStat()
{
    health = PLAYER_MAX_HP;
    bReload = PLAYER_RELOAD;
    reload = 0, maxReload = bReload;
    bSpeed = PLAYER_SPEED;
    bDmg = PLAYER_DMG;
    speed = bSpeed;
    dmg = bDmg;
    mana = PLAYER_MAX_MANA / 3;
    alive = true;
    right = 0, down = 0, left = 0, up = 0;
    atk = 0;
}

void Player::initPos()
{
    //set posititon
    x = SCREEN_WIDTH/2;
    y = SCREEN_HEIGHT/2;
}

void Player::getDmg(const int& hurt)
{
    if (shield_time <= 0) {
        health -= hurt;
        Mix_PlayChannel(SND_PLAYER_HITTED, isHitted, 0);
    }
}

void Player::getItem(Item& it, unsigned int& score)
{
    if (getDistance(it.x,it.y,x,y) < R_player + R_item){
        it.last = 0;
        switch(it.type){
        case HEALH:
            if (health <= PLAYER_MAX_HP - 5) health += 5;
            else health = PLAYER_MAX_HP;
            break;
        case POINT:
            score += 5;
            break;
        case DRUG:
            s_boost = Speed_TIME;
            break;
        case SHIELD:
            shield_time = SHIELD_TIME;
            break;
        case MANA:
            getMana(10);
            break;
        default:
            break;
        }
    }
}

void Player::getMana(const int& bonus)
{
    if (mana < PLAYER_MAX_MANA) mana += bonus;
    if (mana > PLAYER_MAX_MANA) mana = PLAYER_MAX_MANA;
    if (mana < 0) mana = 0;
}


void Player::update(Vec2f& camera,Mouse* mouse,Map* gMap, const Uint32& time)
{
    if (health <= 0) alive = false;

    now = now + 1;
    if (now >= 100000) now = 0;

    updatePos(camera, gMap);

    updateAngle(mouse);

    updateEngine(camera,mouse, gMap, time);
}

void Player::updateAngle(Mouse* mouse)
{
    angle = getAngle(mouse);
}


void Player::updatePos(Vec2f& camera, Map* gMap)
{
    int dx = right - left;
    int dy = down - up;
    if (dx == 0 && dy == 0) return;
    speed = speed / sqrt(dx * dx + dy * dy);
    float newX = x + speed * dx;
    float newY = y + speed * dy;


    int i = newX / BLOCK_SIZE, j = newY / BLOCK_SIZE;
    if (getDistance(newX, newY, (i + 0.5f) * BLOCK_SIZE, (j+ 0.5f) * BLOCK_SIZE) >= gMap->getRadius(j,i))
    {
       if (dx > 0){
            if (newX <= MAP_SIZE) x = newX;
            if (camera.x <= MAX_CAM_X && camera.x >= MIN_CAM_X && x >= SCREEN_WIDTH/2)
                camera.x += min(dx * speed,MAX_CAM_X - camera.x);
        }
        if (dx < 0){
            if (newX >= 0) x = newX;
            if (camera.x <= MAX_CAM_X && camera.x >= MIN_CAM_X && x <= MAX_CAM_X + SCREEN_WIDTH/2)
                camera.x -= min(dx * (-speed), camera.x - MIN_CAM_X);
        }
        if (dy > 0){
            if (newY <= MAP_SIZE) y = newY;
            if (camera.y <= MAX_CAM_Y && camera.y >= MIN_CAM_Y && y >= SCREEN_HEIGHT/2)
                camera.y += min(dy * speed,MAX_CAM_Y - camera.y);
        }
        if (dy < 0){
            if (newY >= 0) y = newY;
            if (camera.y <= MAX_CAM_Y && camera.y >= MIN_CAM_Y && y <= MAX_CAM_Y + SCREEN_HEIGHT/2)
                camera.y -= min(dy * (-speed), camera.y - MIN_CAM_Y);
        }
    }
}

void Player::updateBullet(Vec2f& camera, Mouse* mouse, Map* gMap)
{
    for (auto prop = p_bullets.begin(); prop != p_bullets.end();)
    {
        bool t = prop->update();
        if (prop->type == SKILL1){prop->x = x, prop->y = y;}
        if (t) ++prop;
        else prop = p_bullets.erase(prop);
    }

    if (atk == 1 && reload >= maxReload) shoot(mouse);

    if (skl1 == 1 && mana > ManaCost[SKILL1]) castSkill_1();

    if (skl2 == 1 && mana > ManaCost[SKILL2]) castSkill_2();

    if (reload <= maxReload) reload++;

    fire->angle = angle;
}

void Player::updateEngine(Vec2f& camera,Mouse* mouse, Map* gMap, const Uint32& time)
{
    bDmg = int(sqrtf(time)/350.0f * PLAYER_DMG) + PLAYER_DMG;
    bSpeed = sqrtf(time)/400.0f * PLAYER_SPEED + PLAYER_SPEED;
    bReload = - int(sqrt(time)/(1.67f * sqrt(time) + 450.0f) * PLAYER_RELOAD) + PLAYER_RELOAD;

    updateBullet(camera,mouse,gMap);

    pulse->angle = angle;
    pulse->x = x - (w/2 + 14) * cosf(angle);
    pulse->y = y - (w/2 + 14) * sinf(angle);

    if (shield_time > 0) {
        shield_time--;
    }
    if (s_boost > 0) {
        speed = 1.25f * bSpeed;
        maxReload = 0.72f * bReload;
        pulse->scale = 1.24f;
        s_boost--;
    }
    else {
        speed = bSpeed;
        maxReload = bReload;
        pulse->scale = 1.0f;
    }
    if (now % 24 == 0) getMana();
}

void Player::shoot(Mouse* mouse)
{
    BulletProp newBullet(NOR, x , y , angle ,BULLET_P_SPEED, 4);
    newBullet.dmg = dmg;
    newBullet.R = R_bullet;
    p_bullets.push_back(newBullet);
    reload -= maxReload;
    if (reload < 0) reload = 0;
    Mix_PlayChannel(SND_PLAYER_SHOOT,attack,0);
}

void Player::castSkill_1()
{
    BulletProp newBullet(SKILL1, x , y  , 0 ,0, 4);
    newBullet.dmg = 1.5f * dmg;
    newBullet.R = 12 * R_bullet;
    p_bullets.push_back(newBullet);
    mana -= ManaCost[SKILL1];
    Mix_PlayChannel(SND_PLAYER_ULTI, ulti, 0);
}
void Player::castSkill_2()
{
    BulletProp newBullet(SKILL2, x , y  , angle , BULLET_P_SPEED * 0.8f, 4);
    newBullet.dmg = 0.85f * dmg;
    newBullet.R = 2.8f * R_bullet;
    p_bullets.push_back(newBullet);
    mana -= ManaCost[SKILL2];
}

void Player::drawBullet(const Vec2f& camera)
{
    for (BulletProp& b: p_bullets){
            int temp = b.now / 5;
        switch(b.type){
        case NOR:
            t = {(temp % b.maxFrame) * 48, 0, 48, 32};
            bullet->angle = b.angle;
            bullet->draw(&t, b.x, b.y, 39 , 26 ,1,camera);
            break;
        case SKILL1:
            t = {(temp % b.maxFrame) * 32, 0, 32, 32};
            skill1->draw(&t, b.x, b.y, 2* b.R, 2 * b.R, 1, camera);
            break;
        case SKILL2:
            t = {(temp % b.maxFrame) * 32, 0, 32, 32};
            skill2->draw(&t, b.x, b.y, 2 * b.R, 2 * b.R, 1, camera);
            break;
        }
    }
}


void Player::drawEngine(Vec2f& camera)
{
    if (reload < maxReload/2){
          fire->draw(NULL,x + (w/2 + 7) * cosf(angle) ,y + (w/2 + 7) * sinf(angle) ,40,18,1,camera);
    }

    t = {((now/DELAY) % 4) * 32, 0, 32, 32};
    pulse->draw(&t,camera,1);

    if (shield_time > 0) {
        t = {((now/DELAY) % 4) * 64, 0, 64, 64};
        shield->draw(&t,x,y,80,80,1,camera);
    }
}

void Player::drawHealthBar()
{
    bar->draw(NULL,0,100,30,500,0);
    bar->draw(NULL,SCREEN_WIDTH - 30,100,30,500,0);
    float temp = health * 1.0f /PLAYER_MAX_HP;
    SDL_Rect sr = {0,0, 48, int(temp * 256 )};
    SDL_FRect des = {0,100 + (1 - temp) * 500,30,temp * 500};
    SDL_RenderCopyExF(renderer,health_bar->texture,&sr,&des,180,NULL,SDL_FLIP_NONE);
    temp = mana * 1.0f / PLAYER_MAX_MANA;
    sr = {0,0, 48, int(temp * 256 )};
    des = {SCREEN_WIDTH - 30,100 + (1 - temp) * 500,30,temp * 500};
    SDL_RenderCopyExF(renderer,mana_bar->texture,&sr,&des,180,NULL,SDL_FLIP_NONE);
}


void Player::drawPlayer(Vec2f& camera)
{
    drawBullet(camera);
    draw(NULL,camera,1);
    drawEngine(camera);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}
