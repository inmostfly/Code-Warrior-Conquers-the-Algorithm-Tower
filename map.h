#pragma once
#include <graphics.h>
#include "imageload.h"

class Map {
public:
    static const int ROW = 40;
    static const int COL = 40;//行列最大值
    static const int TILE_SIZE = 32;
    static const int x_bfs1 = 16, y_bfs1 = 10;
    static const int x_bfs2 = 15, y_bfs2 = 11;
    static const int  x_bfs3 = 30, y_bfs3 = 19;
    static const int  x_org = 40, y_org = 19;
	static const int x_greedy_tech = 24, y_greedy_tech = 14;
	static const int x_greedy_normal = 24, y_greedy_normal = 14;
	static const int x_greedy_hard = 24, y_greedy_hard = 14;
    IMAGE floor, wall, goal,envent,exit,coin,transport,notice,trans,box,readme,fire;
	Map(); // 构造函数
	void Map_all(int target[ROW][COL], int type); // 初始化地图
    void load(int map[ROW][COL]);           // 加载贴图
    void draw(int map[ROW][COL]);           // 渲染地图
    bool isWalkable(int x, int y,int map[ROW][COL]); // 判定是否能走
};
