#pragma once
#include "map.h"
#include "mapdata.h"
#pragma comment(lib,"Winmm.lib")
//int map_org[Map::ROW][Map::COL];//外部定义的地图数据
//int map_bfs[Map::ROW][Map::COL];//外部定义的BFS地图数据

//int bits=32;
//bool g_flag=false;
//int FLAG = 1; // 全局变量，是否退出游戏
//int coin = 0;
void initmusic() {
	mciSendString(_T("open ./asset/mainloop.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./asset/bfs.mp3 alias bfsmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./asset/dino.mp3 alias dinomusic"), NULL, 0, NULL);
	mciSendString(_T("open ./asset/dino.mp3 alias transmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./asset/coin.mp3 alias coinmusic"), NULL, 0, NULL);
	mciSendString(_T("open ./asset/transdoor.mp3 alias transdoormusic"), NULL, 0, NULL);
}

//直接调用initmusic()即可初始化音乐播放器