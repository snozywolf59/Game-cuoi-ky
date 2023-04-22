#pragma once

#include "common.h"
#include "Map.h"

//button
#define BUTTON_HEIGHT 120
#define BUTTON_WIDTH 360
#define ING_BUT_W 80
#define ING_BUT_H 80

const SDL_Point p = {0,0};

SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer );

float getAngleGlobal(const float& x1, const float& y1,const float& x2, const float& y2);

//entity

struct Entity
{
    //entity's image
    SDL_Texture* texture;

    //position
    float x,y,angle = 0;

    //dimensions
    int w, h;

    //scale
    float scale = 1;

    //func
    void loadEntity(const string& path,SDL_Renderer* renderer);

    float getAngle(Entity* temp);

    void draw(SDL_Rect* clip, SDL_Renderer* renderer,
              const SDL_Point& camera = p, int atCenter = 0);
    void draw(SDL_Rect* clip,const int& _x,const int& _y, const int& _w,
              const int& _h, SDL_Renderer* renderer,
              int atCenter = 0,const SDL_Point& camera = p);
};

    // delete entity
void clean(Entity* entity,bool del);

//BUTTON
struct Button:Entity
{
    const float default_scale = 1;

    //SDL_Rect selected;
    int now = 0;

    bool beChosen(const int& _x,const int& _y, const int& _w, const int& _h);

    void drawButton(const int& _x,const int& _y, const int& _w, const int& _h,SDL_Renderer* renderer);
};

//MOUSE
struct Mouse:Entity
{
    int real_mouse_x,real_mouse_y;

    void updateMouse(SDL_Point& camera);
};

///////******Write words on screen///////////
struct Word:Entity
{
    TTF_Font* font;

    SDL_Color color;

    void loadFromRenderedText ( string textureText, SDL_Color textColor, SDL_Renderer* renderer);
};

////@@@@@@@@@@//////FIGHTER//////////////@@@@@@//////////

struct Fighter:Entity
{
    //move
    int left = 0, right = 0, up = 0,down = 0;
    float r;

    SDL_Renderer* renderer;

    //base stat
    int health,dmg,reload,speed;
    bool alive = false;

    //check move func
    bool checkLeft(Map& gMap, const int& speed);
    bool checkRight(Map& gMap, const int& speed);
    bool checkUp(Map& gMap, const int& speed);
    bool checkDown(Map& gMap, const int& speed);

    void stop();

    //collision
    bool hitted(Fighter* bullet);
};

////////////////BULLET/////////////////

struct Bullet:Fighter
{
    Entity* fire;

    Bullet(SDL_Renderer* _renderer, const string& bullet_file, const string& bullet_fire_file);

    void update(Map& gMap);
};






