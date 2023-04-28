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

    pulse = new Entity(renderer,file_player_pulse);
    pulse->w = 28;
    pulse->h = 14;
}


void Player::initStat()
{
    health = PLAYER_MAX_HP;
    reload = PLAYER_RELOAD;
    speed = PLAYER_SPEED * frameDelay;
    dmg = PLAYER_DMG;
    alive = true;
    right = 0, left = 0, up = 0, down = 0;
    atk = 0;
}

void Player::initPos()
{
    //set posititon
    x = SCREEN_WIDTH/2;
    y = SCREEN_HEIGHT/2;
}

/****************************************************/

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


void Player::updatePos(Vec2f& camera,Map* gMap)
{
    int nextI = (x + speed * cosf(angle))/BLOCK_SIZE;
    int nextJ = (y + speed * sinf(angle))/BLOCK_SIZE;

    Vec2f direction;
    direction.x = right - left;
    direction.y = down - up;
    float temp = direction.length();
    if (temp == 0) return;
    float d = speed/temp;
    if (left){
        if (x >= MAX_CAM_X + SCREEN_WIDTH/2 + d) x -= d;
        else{
            if (camera.x <= MAX_CAM_X && camera.x >= MIN_CAM_X) camera.x -= min(d,camera.x - MIN_CAM_X);
            if (x >= MIN_CAM_X + d) x -= d;
        }
    }
    if (right){
        if (x <= MIN_CAM_X + SCREEN_WIDTH/2 - d) x += d;
        else{
            if (camera.x <= MAX_CAM_X && camera.x >= MIN_CAM_X) camera.x += min(d,MAX_CAM_X - camera.x);
            if ( x <= MAP_SIZE - d) x += d;
        }
    }
    if (up){
        if (y >= MAX_CAM_Y + SCREEN_HEIGHT/2 + d) y -= d;
        else{
            if (camera.y <= MAX_CAM_Y && camera.y >= MIN_CAM_Y) camera.y -= min(d, camera.y - MIN_CAM_Y);
            if (y >= -SCREEN_WIDTH/2 +d) y -= d;
        }
    }
    if (down){
        if (y <= MIN_CAM_Y + SCREEN_HEIGHT/2 - d) y += d;
        else{
            if (camera.y <= MAX_CAM_Y && camera.y >= MIN_CAM_Y) camera.y += min(d, MAX_CAM_Y - camera.y);
            if ( y <= MAP_SIZE - d) y += d;
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
}


/****************************************************/

void Player::shoot(Mouse* mouse)
{
    FighterProp newBullet(x + w/2 * cosf(angle), y + w/2 * sinf(angle) , angle ,BULLET_P_SPEED, 4*DELAY);
    p_bullets.push_back(newBullet);
    reload = 0;
    Mix_PlayChannel(SND_PLAYER_SHOOT,attack,0);
}

/****************************************************/

void Player::drawEngine(Vec2f& camera)
{
    for (FighterProp& b: p_bullets)
    {
        SDL_Rect t = {b.now/DELAY * 32, 0, 32, 32};
        bullet->angle = b.angle;
        bullet->draw(&t, b.x, b.y, R_bullet * 2, R_bullet * 2,1,camera);
    }

    if (reload < 5){
          bullet->fire->draw(NULL,x + (w/2 + 7) * cosf(angle) ,y + (w/2 + 7) * sinf(angle) ,40,18,1,camera);
    }

    SDL_Rect temp = {((now/DELAY) % 4) * 32, 0, 32, 32};
    pulse->draw(&temp,camera,1);
}

/****************************************************/
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
