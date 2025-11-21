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
std::string GetAppPath() {
	char buf[MAX_PATH];
	GetModuleFileNameA(NULL, buf, MAX_PATH);  // 获取 exe 完整路径
	std::string path(buf);
	size_t pos = path.find_last_of("\\/");
	return path.substr(0, pos); // 去掉 exe 文件名，得到目录
}
