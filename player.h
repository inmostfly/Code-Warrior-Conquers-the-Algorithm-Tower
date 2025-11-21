#pragma once
#include <graphics.h>
#include <string>
#include "text_act.h"
#include "map.h"
#include "imageload.h"
#include<queue>

class Player {
public:
    int x, y;       // 角色坐标
    int dir;        // 方向（0下，1左，2右，3上）
    int frame;      // 当前帧（0-2）
    IMAGE sprite;   // 精灵图像（96×128）
    std::queue<char> inputqueue;
    bool autoMoving = false;
	bool movingtonext = false; // 是否移动到下一个位置
    bool flag_win = false;
    int targetx = 0;
    int targety = 0;
    wchar_t currentcmd;
	int move_count = 0; // 记录移动次数，用于自动移动
    Player();
    bool eventTriggered;//bool类型，事件触发
    std::wstring eventMessage;//字符串，事件消息
    int eventTimer;//事件倒计时，由sleep控制帧率
    int step_num = 0;
    void load();             // 加载人物图
    void update(class Map& map, int temp[Map::COL][Map::ROW]);           // 处理输入、帧更新
    void draw();             // 绘制当前帧
    void setautomove(const std::wstring& input);
};
