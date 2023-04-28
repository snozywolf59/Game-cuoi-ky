#pragma once

#include "Entity.h"
#include "Vec2f.h"


//MAP

const int BLOCK_SIZE = 128;
const int NUM_BLOCKS = 16;
const int MAP_SIZE = NUM_BLOCKS * BLOCK_SIZE;
const int MAX_CAM_Y = MAP_SIZE - SCREEN_HEIGHT;
const int MAX_CAM_X = MAP_SIZE - SCREEN_WIDTH;
const int MIN_CAM_Y = 0;
const int MIN_CAM_X = 0;

bool canMove(const int& x);

enum UniverseObject
{
    Star,
    Earth,
    Moon,
    Planet0,
    Planet1,
    Planet2,
    Num_Of_UniObj
};

const string FILE_UNI_OBJ[] =
{
  "image/Map/Star.png",
  "image/Map/Earth.png",
  "image/Map/Moon.png",
  "image/Map/Planet0.png",
  "image/Map/Planet1.png",
  "image/Map/Planet2.png"
};

const int MAX_FRAME_UNI[] =
{
  4, 77, 60, 1, 1, 1
};

class Map
{
public:
    int map_num[NUM_BLOCKS][NUM_BLOCKS];
    Map(SDL_Renderer* _renderer);
    void loadMap(const string& path);
    bool checkNextMove(const int& nowX, const int& nowY, const float& speed, const float& angle);
    void updateMap();
    void drawMoon();
    void drawEarth();
    void drawNormalPlanet(const int& i);
    void drawMap(const Vec2f& camera);
    void destroy();
private:
    SDL_Rect src,des;
    SDL_Renderer* renderer;
    unsigned int UniObjProp[NUM_BLOCKS][NUM_BLOCKS];

    Entity* planet[Num_Of_UniObj];

    vector <Vec2f> blockObj;
};


