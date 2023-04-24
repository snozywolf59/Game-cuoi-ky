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

    void draw(SDL_Rect* clip,const SDL_Point& camera = p, int atCenter = 0);
    void draw(SDL_Rect* clip,const int& _x,const int& _y, const int& _w,
              const int& _h, int atCenter = 0,const SDL_Point& camera = p);
};

    // delete entity
void clean(Entity* entity,bool del);

//BUTTON
struct Button:Entity
{
    const float default_scale = 1;

    //SDL_Rect selected;
    int now = 0;

    Button(SDL_Renderer* _renderer, const string& path);

    bool beChosen(const int& _x,const int& _y, const int& _w, const int& _h);

    void drawButton(const int& _x,const int& _y, const int& _w, const int& _h);
};

//MOUSE
struct Mouse:Entity
{
    int real_mouse_x, real_mouse_y, now = 0;

    Mouse(SDL_Renderer* _renderer, const string& path);

    void updateMouse(SDL_Point& camera);
};

///////******Write words on screen///////////
struct Word:Entity
{
    TTF_Font* font;

    Entity* pad;

    SDL_Color color;

    Word(SDL_Renderer* renderer, const int& _x = 0, const int& _y = 0);

    void loadFromRenderedText (const string& textureText, SDL_Color textColor, SDL_Renderer* renderer);

    void drawWord();

    void drawWord(const int& _x,const int& _y, const int& _w, const int& _h);
};








