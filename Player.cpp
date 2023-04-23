#include "Player.h"



///////////////////////////PLAYER/////////////////////////


Player::Player(SDL_Renderer* trenderer)
{
    renderer = trenderer;

    loadEntity(file_player);

    initStat();
    initPos();
    initBullet();
}

void Player::initStat()
{
    health = PLAYER_MAX_HP;
    reload = PLAYER_RELOAD;
    speed = PLAYER_SPEED * frameDelay;
    dmg = PLAYER_DMG;
    alive = true;
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

void Player::update(SDL_Point& camera,Mouse* mouse,Map* gMap)
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


void Player::updatePos(SDL_Point& camera,Map* gMap)
{
    float t = sqrt(-1.0+left*left+right*right+up*up+down*down+1.0);
    if(left && camera.x>-SCREEN_WIDTH/2){
            if(checkLeft(*gMap,0)) camera.x -= speed/t;
    }
    if(right && camera.x<MAX_CAM_X){
            if(checkRight(*gMap,0)) camera.x += speed/t;
    }
    if(up && camera.y > -SCREEN_HEIGHT/2){
            if(checkUp(*gMap,0)) camera.y -= speed/t;
    }
    if(down && camera.y < MAX_CAM_Y){
           if(checkDown(*gMap,0)) camera.y += speed/t;
    }
    x = SCREEN_WIDTH/2 - w/2 + camera.x;
    y = SCREEN_HEIGHT/2 - h/2 + camera.y;
}


void Player::updateBullet(SDL_Point& camera, Mouse* mouse, Map* gMap)
{
    for (FighterProp& b: p_bullets)
    {
        b.updatePos();
    }

    if (atk == 1 && reload == PLAYER_RELOAD) shoot(mouse);

    if (reload < PLAYER_RELOAD) reload++;

    bullet->fire->angle = angle;
}


/****************************************************/

void Player::shoot(Mouse* mouse)
{
    FighterProp newBullet(x + w/2 * cos(angle), y + w/2 * sin(angle) , angle ,BULLET_P_SPEED);
    p_bullets.push_back(newBullet);
    reload = 0;
    Mix_PlayChannel(SND_PLAYER_SHOOT,attack,0);
}

/****************************************************/

void Player::drawBullet(SDL_Renderer* renderer,SDL_Point& camera)
{
    for (FighterProp& b: p_bullets)
    {
        bullet->angle = b.angle;
        bullet->draw(NULL, b.x, b.y, bullet->w, bullet->h,renderer,1,camera);
    }

    if (reload < 5){
          bullet->fire->draw(NULL,x + (w/2 + 7) * cos(angle) ,y + (w/2 + 7) * sin(angle) ,40,18,renderer,1,camera);
    }
}

/****************************************************/

void Player::drawPlayer(SDL_Renderer* renderer, SDL_Point& camera)
{
    draw(NULL,renderer,camera,1);
    drawBullet(renderer,camera);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}
