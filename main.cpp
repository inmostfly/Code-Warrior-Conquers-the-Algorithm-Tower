#define UNICODE
#define _UNICODE
#include <graphics.h>
#include "text_act.h"
#include <windows.h>
#include"manager.h"
#pragma comment(lib, "winmm.lib")
#include "map.h"
#include "player.h"
#include "notice.h"
#include "bfs.h"
#include "Mainmaploop.h"
#include "dino_game.h"
#include"mapdata.h"

//此处链接库貌似出现了严重问题 winnm.lib无法链接，已经修复
int map_org[Map::ROW][Map::COL];//外部定义的地图数据
int currentMap[Map::ROW][Map::COL];//外部定义的地图数据,全局的外部地图数据，供各个函数使用
//防底层地图被篡改，从而影响其他函数的使用，浅拷贝地图数据，保证每个函数地图数据独立

int bits = 32;

bool g_flag = false;

int FLAG = 1; // 全局变量，是否退出游戏
int coin = 0;
//int capacity = 35;
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
    save_coin_to_file(coin);
    return 0;
}
