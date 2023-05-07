#include "Item.h"

Item::Item(ITEM _type, const int& _x, const int& _y)
{
    type = _type, x = _x, y = _y;
    now = 0;
    last = Item_Time;
}

void Item::update()
{
    now = (now + 1)%30;
    last--;
}


void spawnItem(vector<Item>& items, const int& x, const int& y, const Uint32& time)
{
   //time increases, rate increases.
   //rate max = 30%, rate min = 50%
   float temp = 20 * time;
   temp /= (time + 320);
   float rate = 20 + temp;
   if ((rand() % 100) <= rate)
   {
       int newR = rand() % 100;
       ITEM type;
       for (int i = NONE; i + 1 < TOTAL_ITEMS; i++){
         if (Ith[i + 1] <= newR && newR < Ith[i+2]){
            type = ITEM(i+1);
            break;
         }
       }
       Item nItem = Item(type,x,y);
       items.push_back(nItem);
   }
}
