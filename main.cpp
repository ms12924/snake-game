#include <ncurses.h> // ncurses 기능 사용
#include "map.hpp" // 맵 출력 함수
#include "snake.hpp" // 뱀 함수
#include "item.hpp" // 아이템 함수
#include "gate.hpp" // 게이트 함수
#include "contents.hpp" // 점수,미션 함수

int currentStage=0; // 현재 스테이지 번호
bool youwin = false; // 게임 클리어 여부 저장

int main(){
    initOriginalMap();
    initscr(); // ncurses 화면 초기화. 항상 맨 처음에 호출
    cbreak(); // 바로 입력받음
    noecho(); // 입력한거 안보이게
    keypad(stdscr, TRUE); // 방향키같은 특수키 인식 가능
    curs_set(0); // 커서 숨기기
    nodelay(stdscr, TRUE); // 프로그램 멈추지 않도록 함

    start_color(); //색상 초기화
    init_color(COLOR_WHITE, 700, 700, 700);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_MAGENTA, 1000, 0, 1000);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(8, 1000, 500, 0);
    init_color(9, 400, 400, 400);
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, 9, 9);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, 8, 8);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);
    init_pair(6, COLOR_RED, COLOR_RED);
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(8, COLOR_BLUE, COLOR_BLUE);

    // 게임 요소 초기화
    initSnake(); // 뱀 생성
    initItems(); // 아이템 생성
    initGate(); // 게이트 생성
    initContents(currentStage); // 점수판, 미션 초기화

    int tick=0; // 틱 체크

    // 게임 오버 전까지 반복
    while (!gameOver){
        int key=getch(); // 키 입력 받기

        //방향키 입력 되도록
        if(key==KEY_UP && dir!=DOWN) dir=UP;
        if(key==KEY_DOWN && dir!=UP) dir=DOWN;
        if(key==KEY_LEFT && dir!=RIGHT) dir=LEFT;
        if(key==KEY_RIGHT && dir!=LEFT) dir=RIGHT;

        
        //반대 방향 입력시 게임오버 되도록
        if((key==KEY_UP && dir==DOWN) || (key==KEY_DOWN && dir==UP) || (key==KEY_LEFT && dir==RIGHT) || (key==KEY_RIGHT && dir==LEFT)){
            // 무적 아니면 반복문 종료
            if(!invincible){
            gameOver=true;
            break;
            }
        }
        

        tick++;
        // 무적 상태 시간 감소
        if(invincible){
            invincibleTimer--;
            // 무적 시간 끝나면 거짓
            if(invincibleTimer<=0) invincible=false;
        }
        if(tick % 10 ==0) score.elapsedTime++; // 일정 시간마다 플레이 시간 증가
        if(tick%3==0){ //0.5초마다 이동

            // 뱀 이동
            Point head = snake.front();
            Point newHead = head;
            if(dir==UP) newHead.y--;
            if(dir==DOWN) newHead.y++;
            if(dir==LEFT) newHead.x--;
            if(dir==RIGHT) newHead.x++;
            int headType=gameMap[currentStage][newHead.y][newHead.x];

            moveSnake(); // 실제 뱀 이동

            // 아이템 먹으면
            if(headType==5 || headType==6){
                applyItem(headType); // 효과 적용
                if(headType==5) score.growthItems++; // 성장 아이템 개수 증가
                if(headType==6) score.poisonItems++; // 독 아이템 개수 증가
            }
            if(headType==7){
                teleportSnake(dir); // 게이트 이동
                score.gateCount++; // 게이트 사용 횟수 증가
            }
            if(headType==8){
                applyItem(headType);
            }
        }
        updateItems(); // 아이템 상태 업데이트
        updateScore(); // 점수 업데이트

        // 현재 스테이지 미션 성공 여부 확인
        if(checkMission(currentStage)){
            currentStage++; // 다음 스테이지로 이동
            youwin=true;

            // 모든 스테이지 완료 시 게임 클리어
            if(currentStage >= STAGE_COUNT){
                mvprintw(MAP_SIZE/2, MAP_SIZE-6, "YOU WIN!");
                refresh();
                napms(2000);
                break;
            }

            // 다음 스테이지 초기화
            resetMap(currentStage);
            initSnake();
            initItems();
            initGate();
            initContents(currentStage);
        }

        drawMap(currentStage); // 현재 맵 상태
        drawContents(); // 점수판, 미션 출력
        refresh(); // 화면에 반영
        napms(100); //0.1초 대기

    }

    // 게임오버가 되었을 때
    if(!youwin){
    mvprintw(MAP_SIZE/2, MAP_SIZE-4, "GAME OVER");
    refresh(); 
    napms(2000); // 게임오버 화면 2초 동안 유지
    }

    endwin(); // ncurses 종료
    return 0; // 프로그램 종료
}
