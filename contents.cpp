#include "contents.hpp"
#include "map.hpp"
#include "snake.hpp"
#include <ncurses.h>

extern int currentStage;

Score score;

Mission missions[4]={ // 미션 : 길이, 성장아이템(초록사과), 독아이템(빨간사과), 게이트
    {5, 3, 2, 1},
    {7, 5, 3, 2},
    {10, 7, 4, 3},
    {13, 9, 5, 4}
};

// 뱀 기본 초기화
void initContents(int stage){
    score.currentLength = snake.size();
    score.maxLength = snake.size();
    score.growthItems = 0;
    score.poisonItems = 0;
    score.gateCount = 0;
    score.elapsedTime = 0;
}

// 점수 갱신하는 함수
void updateScore(){
    score.currentLength = snake.size();
    if(score.currentLength > score.maxLength) // 최대길이 갱신하기
        score.maxLength = score.currentLength;
}

// 오른쪽 상태창
void drawContents(){ 
    int col = MAP_SIZE * 2 + 2;
    for(int i=1; i<=13; i++)
        mvprintw(i, col, "                               ");
    // 출력하는 내용 순서대로
    mvprintw(1, col, "Score Board"); // 여기부터 점수판
    mvprintw(2, col, "B: %d / %d", score.currentLength, score.maxLength); // 현재 길이, 최대 길이
    mvprintw(3, col, "+: %d", score.growthItems); // 성장아이템 먹은 수
    mvprintw(4, col, "-: %d", score.poisonItems); // 독 아이템 먹은 수
    mvprintw(5, col, "G: %d", score.gateCount); // 게이트 통과 횟수
    mvprintw(6, col, "Time: %ds", score.elapsedTime); // 플레이 시간

    mvprintw(8, col, "Mission"); // 여기부터 미션
    mvprintw(9, col, "B: %d (%s)", missions[currentStage].targetLength, // 목표 길이
        score.currentLength >= missions[currentStage].targetLength ? "v" : " ");
    mvprintw(10, col, "+: %d (%s)", missions[currentStage].targetGrowth, // 각각 미션 성공여부 체크표시(v)
        score.growthItems >= missions[currentStage].targetGrowth ? "v" : " ");
    mvprintw(11, col, "-: %d (%s)", missions[currentStage].targetPoison,
        score.poisonItems >= missions[currentStage].targetPoison ? "v" : " ");
    mvprintw(12, col, "G: %d (%s)", missions[currentStage].targetGate,
        score.gateCount >= missions[currentStage].targetGate ? "v" : " ");
}

bool checkMission(int stage){ // 미션 목표 달성하면 최종적으로 true 반환
    return score.currentLength >= missions[stage].targetLength &&
           score.growthItems >= missions[stage].targetGrowth &&
           score.poisonItems >= missions[stage].targetPoison &&
           score.gateCount >= missions[stage].targetGate;
}
