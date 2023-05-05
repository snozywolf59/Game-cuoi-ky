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
   //rate max = 50%, rate min = 20%
   float temp = 3000.0f / time;
   float rate = 20 + min(30.0f,temp);
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
       cout << newR << ' ' << type << endl;
       Item nItem = Item(type,x,y);
       items.push_back(nItem);
   }
}
