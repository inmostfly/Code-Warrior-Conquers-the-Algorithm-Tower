#define UNICODE
#define _UNICODE
#include <graphics.h>
#include "text_act.h"
#include <windows.h>
#include "map.h"
#include "player.h"
#include "notice.h"
#include "bfs.h"
#include "Mainmaploop.h"
#include "dino_game.h"
#include"mapdata.h"

int map_org[Map::ROW][Map::COL];//外部定义的地图数据
int map_bfs[Map::ROW][Map::COL];//外部定义的地图数据
int bits = 32;

bool g_flag = false;

int FLAG = 1; // 全局变量，是否退出游戏
int coin = 0;
int coin_count = 0;
int fire_count = 0;
int trans_count = 0;
int pass_flag1 = 0;
int pass_flag2 = 0;
int step_max = 100; // 最大步数限制


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    initmusic();
    while (FLAG)
    {
        Mainmaploop();
    }
    return 0;
}
