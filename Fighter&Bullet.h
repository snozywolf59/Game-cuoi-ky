#pragma once

#include "Entity.h"
#include "Map.h"

const float BULLET_P_SPEED = 0.63f * frameDelay;
const float R_bullet = 13.3;

const int DELAY = 7;

enum BULLET{
    NOR,
    SKILL1,
    SKILL2
};

const float BulletMaxS[] = {1000, 900, MAP_SIZE};
const int ManaCost[] = {0, 180, 60};
const float BulletReload[] = {1, 3, 3};

struct FighterProp
{

    float x, y, angle, speed;
    int now, maxFrame, dmg;
    float R;

    FighterProp(const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = 0,const int& _dmg = 1, const int& _maxFrame = 0);

    void updateAngle(const int& _x, const int& _y);
};

struct BulletProp:FighterProp{
    BULLET type;

    float s, maxS;

    BulletProp(BULLET _type, const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = 0, const int& _maxFrame = 0);

    bool update();
};



