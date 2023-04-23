#pragma once

#include "Entity.h"

const float BULLET_P_SPEED = 0.6;
const float R_bullet = 3;

bool checkLeft(Map& gMap, const int& speed);
bool checkRight(Map& gMap, const int& speed);
bool checkUp(Map& gMap, const int& speed);
bool checkDown(Map& gMap, const int& speed);
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
    int now, maxFrame;

    FighterProp(const float& x_ = 0,const float& y_ = 0,const float& angle_ = 0,
                const float& _speed = 0, const int& _maxFrame = 0);

    void updatePos();

    void updateAngle(const int& _x, const int& _y);

    void draw(Entity* x,const SDL_Point& camera, int now = -1);
};

