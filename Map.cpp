#include "Map.h"

int i, j, nextI, nextJ;

//MAP
bool canMove(const int& x)
{
    if (x <= 3) return true;
    return false;
}

/****************************************************/

Map::Map(SDL_Renderer* _renderer)
{
    renderer = _renderer;
    for (int i = 0; i < Num_Of_UniObj;i++){
        planet[i] = new Entity(renderer,FILE_UNI_OBJ[i]);
    }
}

void Map::loadMap(const string& path)
{

    ifstream read(path);
    int cnt = 0, x;
    while (cnt < NUM_BLOCKS * NUM_BLOCKS)
    {
        read >> x;
        map_num[cnt / NUM_BLOCKS][cnt % NUM_BLOCKS] = x;

        if ( x < 0 || x >= Num_Of_UniObj)
        {
            cerr << "Invalid map num\n";
            exit(0);
        }

        if (!canMove(x))
        {
            blockObj.push_back(Vec2f(cnt/NUM_BLOCKS, cnt%NUM_BLOCKS));
        }

        UniObjProp[cnt / NUM_BLOCKS][cnt % NUM_BLOCKS] = rand()%100;

        cnt++;
    }
    read.close();
}

/****************************************************/

bool Map::checkNextMove(const int& nowX, const int& nowY, const float& speed, const float& angle)
{

}


void Map::updateMap()
{
    for (i = 0; i < NUM_BLOCKS; i++)
        for (j = 0; j < NUM_BLOCKS; j++)
        UniObjProp[i][j] = (UniObjProp[i][j] + 1)%640;
}


void Map::drawMap(const Vec2f& camera)
{
    int type = 0;

    int start_j = camera.x/BLOCK_SIZE , start_i = camera.y/BLOCK_SIZE;

    des.h = BLOCK_SIZE;
    des.w = BLOCK_SIZE;

    for (i = start_i; i < start_i + SCREEN_HEIGHT/BLOCK_SIZE+3; i++)
    {
        if (i < 0 || i > NUM_BLOCKS-1) continue;
        des.y = -camera.y + i * BLOCK_SIZE;
        for (j = start_j; j < start_j + SCREEN_WIDTH/BLOCK_SIZE + 3; j++)
        {
            if (j < 0 || j > NUM_BLOCKS-1) continue;

            type = map_num[i][j];

            des.x = -camera.x + j * BLOCK_SIZE;

            src = {((UniObjProp[i][j]/15) % 4) * 128,0,128,128};
            planet[Star]->draw(&src,des.x,des.y,des.w,des.h);

            if (type != 0)
            {
                if (type < 3) src = {((UniObjProp[i][j]/10) % 8) * 128, ((UniObjProp[i][j]/10) / 8) * 128,128,128};
                else src = {((UniObjProp[i][j]/10) % 8) * 256, ((UniObjProp[i][j]/10) / 8) * 256,256,256};
                planet[type]->draw(&src,des.x,des.y,des.w,des.h);
            }
        }
    }

    planet[Planet3]->draw(NULL,115,825,planet[Planet3]->w,planet[Planet3]->h,0,camera);
}

/****************************************************/
void Map::destroy()
{
    for (i = 0; i < Num_Of_UniObj; i++){
        clean(planet[i],1);
    }
}



