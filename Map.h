#pragma once

#include "common.h"


//MAP

#define BLOCK_SIZE 60
#define MAP_SIZE 30
const int MAX_CAM_Y = (MAP_SIZE*BLOCK_SIZE)-(SCREEN_HEIGHT/2);
const int MAX_CAM_X = (MAP_SIZE*BLOCK_SIZE)-(SCREEN_WIDTH/2);

bool canMove(const int& x);

struct Map
{
    SDL_Rect src,des;

    SDL_Texture* wall;
    SDL_Texture* dirt;

    int map_num[MAP_SIZE][MAP_SIZE];

    int way[(MAP_SIZE-2)*(MAP_SIZE-2)];
    int count_way;

    void loadMap(string path);
    void drawMap(SDL_Renderer* renderer,SDL_Point& camera);

    void destroy();
};


