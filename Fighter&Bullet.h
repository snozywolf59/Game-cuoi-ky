#pragma once

#include "Entity.h"
#include "Map.h"

const float BULLET_P_SPEED = 0.6;
const float R_bullet = 12;

const int DELAY = 7;

////////////////BULLET/////////////////

struct Bullet:Entity
{
    Entity* fire;

    float speed;

    Bullet(SDL_Renderer* _renderer, const string& bullet_file, const string& bullet_fire_file);

    void update(Map& gMap);
};


struct FighterProp
{
    float x, y, angle, speed;
    int now, maxFrame, dmg;
    float s , R;

    FighterProp(const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = 0,const int& _dmg = 1, const int& _maxFrame = 0);

    void updatePos();

    void updateAngle(const int& _x, const int& _y);

    void draw(Entity* x,const Vec2f& camera, int now = -1);
};

