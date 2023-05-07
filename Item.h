#pragma once

#include "Entity.h"

enum ITEM
{
    NONE = -1,
    POINT ,
    DRUG ,
    MANA ,
    HEALH ,
    SHIELD ,
    TOTAL_ITEMS
};

const int R_item = 10;
//Ith: Item Threshold
const int Ith[] = {0,32,52,70,90,100};

const int Item_Time = 12 * FPS;

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

