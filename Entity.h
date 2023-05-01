#pragma once

#include "common.h"
#include "Vec2f.h"

const Vec2f p = {0,0};

SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer );

float getAngleGlobal(const float& x1, const float& y1,const float& x2, const float& y2);

float getDistance(const float& x1, const float& y1,const float& x2, const float& y2);

//entity

struct Entity
{
    //entity's image
    SDL_Texture* texture;
    SDL_Renderer* renderer;

    //position
    float x,y,angle = 0;

    //dimensions
    int w, h;

    //scale
    float scale = 1;

    Entity();

    Entity(SDL_Renderer* _renderer, const string& path, const int& _x = 0, const int& _y = 0);

    //func
    void loadEntity(const string& path);

    float getAngle(Entity* temp);

    void draw(SDL_Rect* clip,const Vec2f& camera = p, int atCenter = 0);
    void draw(SDL_Rect* clip,const int& _x,const int& _y, const int& _w,
              const int& _h, int atCenter = 0,const Vec2f& camera = p);
};

    // delete entity
void clean(Entity* entity,bool del);




