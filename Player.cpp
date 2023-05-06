#include "Player.h"

///////////////////////////PLAYER/////////////////////////

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

    bullet = new Bullet(renderer,file_player_bullet,file_player_bullet_fire);
    shield = new Entity(renderer, file_player_shield);
    pulse = new Entity(renderer,file_player_pulse);
    pulse->w = 28;
    pulse->h = 14;
    attack = Mix_LoadWAV(snd_player_shoot);
    isHitted = Mix_LoadWAV(snd_player_hitted);

}


void Player::initStat()
{
    health = PLAYER_MAX_HP;
    reload = PLAYER_RELOAD;
    speed = PLAYER_SPEED;
    dmg = PLAYER_DMG;
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
        case SHIELD:
            shield_time = SHIELD_TIME;
            break;
        }
    }
}

void Player::update(Vec2f& camera,Mouse* mouse,Map* gMap)
{
    if (health <= 0) alive = false;

    now = (now + 1)%100;

    updatePos(camera, gMap);

    updateAngle(mouse);

    updateEngine(camera,mouse, gMap);
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
    speed = PLAYER_SPEED / sqrt(dx * dx + dy * dy);
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
        prop->updatePos();
        prop->now = (prop->now + 1)%prop->maxFrame;
        if (prop->s > player_range)
        {
            prop = p_bullets.erase(prop);
        }
        else ++prop;
    }

    if (atk == 1 && reload == PLAYER_RELOAD) shoot(mouse);

    if (reload < PLAYER_RELOAD) reload++;

    bullet->fire->angle = angle;
}

void Player::updateEngine(Vec2f& camera,Mouse* mouse, Map* gMap)
{
    updateBullet(camera,mouse,gMap);

    pulse->angle = angle;
    pulse->x = x - (w/2 + 14) * cosf(angle);
    pulse->y = y - (w/2 + 14) * sinf(angle);

    if (shield_time > 0) {
        shield_time--;
    }
}

void Player::shoot(Mouse* mouse)
{
    FighterProp newBullet(x + w/2 * cosf(angle), y + w/2 * sinf(angle) , angle ,BULLET_P_SPEED,dmg, 4*5);
    p_bullets.push_back(newBullet);
    reload = 0;
    Mix_PlayChannel(SND_PLAYER_SHOOT,attack,0);
}

void Player::drawEngine(Vec2f& camera)
{
    SDL_Rect t;
    for (FighterProp& b: p_bullets)
    {
        t = {b.now/5 * 48, 0, 48, 32};
        bullet->angle = b.angle;
        bullet->draw(&t, b.x, b.y, 48 , 32,1,camera);
    }

    if (reload < 5){
          bullet->fire->draw(NULL,x + (w/2 + 7) * cosf(angle) ,y + (w/2 + 7) * sinf(angle) ,40,18,1,camera);
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

    bar->draw(NULL,0,75,50,500,0);
    float temp = health * 1.0f /PLAYER_MAX_HP;
    SDL_Rect sr = {0,0, 48, int(temp * 256 )};
    SDL_Rect des = {0,75 + (1 - temp) * 500,50,int(temp * 500)};
    SDL_RenderCopyEx(renderer,health_bar->texture,&sr,&des,180,NULL,SDL_FLIP_NONE);
}


void Player::drawPlayer(Vec2f& camera)
{
    draw(NULL,camera,1);
    drawEngine(camera);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}
