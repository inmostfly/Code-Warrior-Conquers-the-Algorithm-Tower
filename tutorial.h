#pragma once
#include"mapdata.h"
#include<queue>
#include"button.h"
#define WINDOW_WIDTH 960	// 窗口宽度
#define WINDOW_HEIGHT 640	// 窗口高度
#define MAP_COL 20		// 地图列数
#define MAP_ROW 20		// 地图行数
#define PASS 0			// 允许通行
#define IMPASS 1		// 禁止通行
#define VISITED 2		// 已访问，标记为红色
#define VISITING 3		// 正在访问的位置
#define IMPASS_NUM 40	// 禁止通行的数目
#define SIDE_LENGTH	30	// 每一小格的边长
#define MAP_WIDTH SIDE_LENGTH * MAP_COL	// 地图宽度
#define MAP_HEIGHT SIDE_LENGTH * MAP_ROW	// 地图高度
#define BUTTON_WIDTH 300	// 按钮宽度
#define BUTTON_HEIGHT 200	// 按钮高度
#define BUTTON_INTERVAL 100	// 按钮间隔（水平间隔）
#define DELAYTIME 25	//延迟，间隔时间，毫秒单位
using namespace std;
struct rect // 矩形
{
	int x, y;
	int color;
};

struct button // 按钮
{
	int x, y, w, h;
	const wchar_t text[100];
	int color;
};
pair<int, int> randxy(); // 生成随机起点
void initmap(int m[MAP_ROW + 5][MAP_COL + 5]); // 初始化地图
void rebackmap(int m[MAP_ROW + 5][MAP_COL + 5]); // 回溯整张地图
void printmap(int m[MAP_ROW + 5][MAP_COL + 5]);// 输出地图
void paintrect(rect r); // 绘画一个矩形
void paintbutton(button bt); // 绘画一个按钮
bool isbuttondown(button bt, MOUSEMSG m); // 判断点击是否在按钮内
void paintmap(int m[MAP_ROW + 5][MAP_COL + 5]); // 绘画地图
void dfs(int m[MAP_ROW + 5][MAP_COL + 5], int x, int y); // 深搜模拟
void bfs(int m[MAP_ROW + 5][MAP_COL + 5], int x, int y); // 广搜模拟
void tutorial(); // 主函数


