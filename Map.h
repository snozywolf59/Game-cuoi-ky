#pragma once

#include "Entity.h"
#include "Vec2f.h"


//MAP

const int BLOCK_SIZE = 128;
const int NUM_BLOCKS = 12;
const int MAP_SIZE = NUM_BLOCKS * BLOCK_SIZE;
const int MAX_CAM_Y = MAP_SIZE - SCREEN_HEIGHT;
const int MAX_CAM_X = MAP_SIZE - SCREEN_WIDTH;
const int MIN_CAM_Y = 0;
const int MIN_CAM_X = 0;

enum UniverseObject
{
    Star,
    Earth,
    Moon,
    Planet2,
    Planet3,
    Num_Of_UniObj
};

const string FILE_UNI_OBJ[] =
{
  "image/Map/Star.png",
  "image/Map/Earth.png",
  "image/Map/Moon.png",
  "image/Map/Planet2.png",
  "image/Map/Planet3.png"
};

const int MAX_FRAME_UNI[] =
{
  4, 77, 60, 1,
};

class Map
{
public:
    vector <Vec2f> Obstacles;
    Map(SDL_Renderer* _renderer);
    void loadMap(const string& path);
    void updateMap();
    void drawMap(const Vec2f& camera);
    void destroy();
    int getPlanet(const int& row, const int& col);
    int getRadius(const int& row, const int& col);
    int getNumObs();
private:
    SDL_Rect src,des;
    int Num_Obstacles;
    SDL_Renderer* renderer;
    unsigned int UniObjProp[NUM_BLOCKS][NUM_BLOCKS];
    int map_num[NUM_BLOCKS][NUM_BLOCKS];
    Entity* planet[Num_Of_UniObj];
};


