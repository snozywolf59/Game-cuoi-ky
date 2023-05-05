#pragma once

#include "Entity.h"

enum ITEM
{
    NONE = -1,
    POINT ,
    HEALH ,
    SHIELD ,
    TOTAL_ITEMS
};

const int R_item = 10;
//Ith: Item Threshold
const int Ith[] = {0,50,80,100};

const int Item_Time = 10 * FPS;

struct Item
{
    ITEM type;
    int x,y;
    int now;
    int last;
    Item(ITEM _type, const int& _x, const int& _y);

    void update();
};


void spawnItem(vector <Item>& items,const int& x, const int& y, const Uint32& time);

