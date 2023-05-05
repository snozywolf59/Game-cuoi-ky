#include "Item.h"

Item::Item(ITEM _type, const int& _x, const int& _y)
{
    type = _type, x = _x, y = _y;
    now = 0;
}

void Item::update()
{
    now = (now + 1)%42;
    last--;
}


void spawnItem(vector<Item>& items, const int& x, const int& y, const Uint32& time)
{
   //thoi gian cang tang, rate sinh ra cang giam.
   //rate max = 30%, rate min = 10%
   float temp = 6300.0f / time;
   float rate = 10 + min(20.0f,temp);
   if ((rand() % 100) <= rate)
   {
       int newR = rand() % 100;
       ITEM type;
       for (int i = NONE; i < TOTAL_ITEMS - 1; i++){
         if (Ith[i] <= newR && newR < Ith[i+1]){
            type = ITEM(i+1);
            break;
         }
       }
       Item nItem = Item(type,x,y);
       items.push_back(nItem);
   }
}
