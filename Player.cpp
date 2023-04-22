#include "Player.h"

BulletProp::BulletProp()
{
    x = 0, y = 0, angle = 0;
}

BulletProp::BulletProp(const float& x_, const float& y_, const float& angle_, const int& _speed)
{
    x = x_, y = y_, angle = angle_;
    speed = _speed;
}

///////////////////////////PLAYER/////////////////////////


Player::Player(SDL_Renderer* trenderer)
{
    renderer = trenderer;

    loadEntity(file_player,renderer);

    initStat();
    initPos();
    initBullet();
}

void Player::initStat()
{
    health = PLAYER_MAX_HP;
    reload = PLAYER_RELOAD;
    speed = PLAYER_SPEED;
    dmg = PLAYER_DMG;
    alive = true;
    r = w/2;
}

void Player::initPos()
{
    //set posititon
    x = SCREEN_WIDTH/2;
    y = SCREEN_HEIGHT/2;
}

void Player::initBullet()
{
    bullet = new Bullet(renderer,file_player_bullet,file_player_bullet_fire);

}


/****************************************************/

void Player::update(SDL_Point& camera,Mouse* mouse,Map& gMap)
{
    if (health <= 0) alive = false;

    updatePos(camera, gMap);

    updateAngle(mouse);

    updateBullet(camera,mouse, gMap);
}

void Player::updateAngle(Mouse* mouse)
{
    angle = getAngle(mouse);
}


void Player::updatePos(SDL_Point& camera,Map& gMap)
{
    float t = sqrt(-1.0+left*left+right*right+up*up+down*down+1.0);
    if(left && camera.x>-SCREEN_WIDTH/2){
            if(checkLeft(gMap,PLAYER_SPEED)) camera.x -= PLAYER_SPEED/t;
    }
    if(right && camera.x<MAX_CAM_X){
            if(checkRight(gMap,PLAYER_SPEED)) camera.x += ceil(PLAYER_SPEED/t);
    }
    if(up && camera.y > -SCREEN_HEIGHT/2){
            if(checkUp(gMap,PLAYER_SPEED)) camera.y -= PLAYER_SPEED/t;
    }
    if(down && camera.y < MAX_CAM_Y){
           if(checkDown(gMap,PLAYER_SPEED)) camera.y += ceil(PLAYER_SPEED/t);
    }
    x = SCREEN_WIDTH/2 - w/2 + camera.x;
    y = SCREEN_HEIGHT/2 - h/2 + camera.y;
}


void Player::updateBullet(SDL_Point& camera, Mouse* mouse, Map& gMap)
{
    for (BulletProp& b: p_bullets)
    {
        b.x += b.speed * cos(b.angle);
        b.y += b.speed * sin(b.angle);
    }

    if (atk == 1 && reload == PLAYER_RELOAD) shoot(mouse);

    if (reload < PLAYER_RELOAD) reload++;

    bullet->fire->angle = angle;
}


/****************************************************/

void Player::shoot(Mouse* mouse)
{
    BulletProp newBullet(x + r * cos(angle), y + r * sin(angle) , angle ,15);
    p_bullets.push_back(newBullet);
    reload = 0;
}

/****************************************************/

void Player::drawBullet(SDL_Renderer* renderer,SDL_Point& camera,float scale)
{
    for (BulletProp& b: p_bullets)
    {
        bullet->angle = b.angle;
        bullet->draw(NULL, b.x, b.y, bullet->w, bullet->h,renderer,1,camera);
    }

    if (reload < 5){
          bullet->fire->draw(NULL,x + (r + 7) * cos(angle) ,y + (r + 7) * sin(angle) ,40,18,renderer,1,camera);
    }
}

/****************************************************/

void Player::drawPlayer(SDL_Renderer* renderer, SDL_Point& camera)
{
    draw(NULL,renderer,camera,1);
    drawBullet(renderer,camera);
    SDL_SetRenderDrawColor(renderer,255,20,20,255);
    SDL_RenderDrawPoint(renderer,x + r * cos(angle) - camera.x,y + r * sin(angle)- camera.y);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}
