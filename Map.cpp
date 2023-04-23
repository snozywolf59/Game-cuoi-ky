#include "Map.h"

//MAP
bool canMove(const int& x)
{
    if (x == 0) return true;
    return false;
}

/****************************************************/

void Map::loadMap(string path)
{
    count_way = 0;
    ifstream read(path);
    int cnt = 0, x;
    while (cnt < MAP_SIZE*MAP_SIZE)
    {
        read >> x;
        map_num [cnt/MAP_SIZE][cnt%MAP_SIZE] = x;
        if (canMove(x))
        {
            way[count_way] = cnt;
            count_way++;
        }
        cnt++;
    }
    read.close();
}

/****************************************************/

void Map::drawMap(SDL_Renderer* renderer, SDL_Point& camera)
{
    int type = 0;

    int start_j = camera.x/BLOCK_SIZE , start_i = camera.y/BLOCK_SIZE;

    des.h = BLOCK_SIZE;
    des.w = BLOCK_SIZE;

    //cout << start_i << ' ' << start_j <<'\n';

    for (int i=start_i;i<start_i+SCREEN_HEIGHT/BLOCK_SIZE+3;i++)
    {
        if (i < 0 || i > MAP_SIZE-1) continue;
        des.y = -camera.y+i*BLOCK_SIZE;
        for (int j=start_j;j<start_j+SCREEN_WIDTH/BLOCK_SIZE+3;j++)
        {
            if (j < 0 || j > MAP_SIZE-1) continue;

            type = this->map_num[i][j];

            des.x = -camera.x+j*BLOCK_SIZE;

            switch (type)
            {
            case 2:
                SDL_RenderCopy(renderer,dirt,NULL,&des);
                break;
            case 5:
                SDL_RenderCopy(renderer,wall,NULL,&des);
                break;
            }
        }
    }
}

/****************************************************/
void Map::destroy()
{
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(wall);
    dirt = nullptr;
    wall = nullptr;

}



