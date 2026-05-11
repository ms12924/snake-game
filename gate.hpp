#ifndef GATE_HPP
#define GATE_HPP

#include "map.hpp"
#include "snake.hpp"

// gate
struct Gate{
    int y,x; // 게이트 좌표
    bool active; // 게이트 활성화 여부 저장
};

extern Gate gates[2]; // 게이트 2개 저장하는 배열

void initGate(); // 게이트 초기화
void spawnGate(); // 게이트 생성
Direction getExitDir(int gateIdx, Direction enterDir); // 게이트 통과시 나오는 방향 계산
void teleportSnake(Direction enterDir); // 뱀이 게이트 통과하도록 이동

#endif
