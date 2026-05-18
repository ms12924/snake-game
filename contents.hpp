#ifndef CONTENTS_HPP
#define CONTENTS_HPP

// 게임의 점수 및 현재 상태
struct Score{
    int currentLength; // 현재 뱀의 길이
    int maxLength; // 이번 스테이지에서 달성한 뱀의 최대 길이
    int growthItems; // 먹은 성장 아이템의 총 개수
    int poisonItems; // 먹은 독 아이템의 총 개수
    int gateCount; // 게이트를 통과한 횟수
    int elapsedTime; // 게임 진행 시간 (초 단위)
};

// 스테이지별 클리어 조건
struct Mission{
    int targetLength; // 목표 뱀 길이
    int targetGrowth; // 목표 성장 아이템 획득 개수
    int targetPoison; // 목표 독 아이템 획득 개수
    int targetGate; // 목표 게이트 통과 횟수
};

extern Score score;
extern Mission missions[4];

// 전역 Score 구조체 및 게임 콘텐츠 상태를 초기화하는 함수 (stage: 초기화할 스테이지 번호)
void initContents(int stage);
void updateScore(); // 실시간으로 뱀의 길이를 체크하여 현재 점수 및 최대 길이를 갱신하는 함수
void drawContents(); // ncurses 화면 우측에 점수판과 미션 상태를 출력하는 함수
bool checkMission(int stage);  // 현재 스테이지의 미션 조건을 모두 달성했는지 체크하는 함수

#endif
