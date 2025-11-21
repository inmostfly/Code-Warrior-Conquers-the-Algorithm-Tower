#pragma once
#include <graphics.h>
#include "mapdata.h"
// 恐龙结构体
struct Dino {
    int x, y;       // 位置
    int vy;         // 垂直速ddddddww度
    bool jumping;   // 是否在跳跃
    int w, h;       // 尺寸
};

// 障碍物结构体
struct Obstacle {
    int x, y;
    int w, h;
    bool passed;    // 是否已被越过（加分用）
};
struct Bird {
    int x, y;
    int w, h;
    bool passed;
};

// 游戏函数
void runDinoGame();
