#include "Fighter&Bullet.h"

/////////////////////////////BULLET//////////////////////////////////////
Bullet::Bullet(SDL_Renderer* _renderer, const string& bullet_file, const string& bullet_fire_file)
{
    renderer = _renderer;
    loadEntity(bullet_file);
    speed = BULLET_P_SPEED * frameDelay;
    fire = new Entity(renderer,bullet_fire_file);
}

void Bullet::update(Map& gMap)
{
    x = x + speed*cos(angle);
    y = y + speed*sin(angle);
}

FighterProp::FighterProp(const float& x_, const float& y_, const float& angle_,
                          const float& _speed, const int& _dmg, const int& _maxFrame)
{
    x = x_, y = y_, angle = angle_;
    speed = _speed * frameDelay, maxFrame = _maxFrame;
    dmg = _dmg;
    now = 0, s = 0;
}

void FighterProp::updateAngle(const int& _x, const int& _y)
{
    angle = getAngleGlobal(x,y,_x,_y);
}

void FighterProp::updatePos()
{
    x  = x + speed * cos(angle);
    y  = y + speed * sin(angle);
    s += sqrt(speed * speed);
}


