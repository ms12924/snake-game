#ifndef ITEM_HPP
#define ITEM_HPP

#include "map.hpp"

//랜덤 위치 생성에 필요
#include <cstdlib>
#include <ctime>

//5:growth
//6:poison

struct Item{
    int y, x;
    int type;
    int timer;
};

const int MAX_ITEMS=3;  //동시에 3개까지만 아이템 출현
const int ITEM_DURATION=50; //아이템은 5초동안 지속

extern Item items[MAX_ITEMS]; 

void initItems(); //아이템 초기화
void spawnItem(); //랜덤위치에 생성
void updateItems(); 
void applyItem(int type);

#endif