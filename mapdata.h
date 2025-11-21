#pragma once
#include"map.h"
//全局依赖
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include<string>
#include<shellapi.h>
#include <mmsystem.h>
#include <ctime>
#include <cstdlib>
#include<easyx.h>
extern int map_org[Map::ROW][Map::COL];//外部定义的地图数据
extern int map_bfs[Map::ROW][Map::COL];//外部定义的BFS地图数据

extern int bits;
extern bool g_flag; // 全局变量，表示是否进入BFS关卡
extern int FLAG; // 全局变量，是否退出游戏
extern int coin;
extern int coin_count;
extern int fire_count;
extern int trans_count;
extern int step_max; // 最大步数限制

void initmusic();
std::string GetAppPath();