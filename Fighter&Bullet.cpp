#include "Fighter&Bullet.h"


FighterProp::FighterProp(const float& x_, const float& y_, const float& angle_,
                          const float& _speed, const int& _dmg, const int& _maxFrame)
{
    x = x_, y = y_, angle = angle_;
    speed = _speed * frameDelay, maxFrame = _maxFrame;
    dmg = _dmg;
    now = 0;
}

void FighterProp::updateAngle(const int& _x, const int& _y)
{
    angle = getAngleGlobal(x,y,_x,_y);
}

BulletProp::BulletProp(BULLET _type, const float& x_, const float& y_, const float& angle_, const float& _speed, const int& _maxFrame)
{
    type = _type;
    x = x_, y = y_, angle = angle_;
    speed = _speed , maxFrame = _maxFrame;
    R = R_bullet;
    maxS = BulletMaxS[type];
    now = 0, s = 0, dmg = 0;
}

bool BulletProp::update()
{
    Vec2f d = Vec2f(speed * cosf(angle), speed * sinf(angle));
    switch(type)
    {
    case NOR:
        if (s > maxS) return false;
        x += d.x, y += d.y;
        s += d.length();
        now++;
        break;
    case SKILL2:
        if (s < maxS){
            x += d.x, y += d.y;
            s += d.length();
            ++now;
            if ( s >= maxS) now = 0;
        }else ++now;
        break;
    case SKILL1:
        now++;
        if (now >= 2 * FPS) return false;
        break;
    }
    return true;
}


