#pragma once
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <graphics.h>
#include <iostream>

// 定义玩家记录结构体
struct PlayerRecord {
    std::wstring name; // 玩家名字
    int coins;         // 金币数量

    // 重载比较运算符，用于排序（金币多的排前面）
    bool operator>(const PlayerRecord& other) const {
        return coins > other.coins;
    }
};

class Leaderboard {
private:
    const std::string filename = "rank.txt"; // 排行榜数据文件
    const int MAX_RECORDS = 10;              // 最多保存前10名
    std::vector<PlayerRecord> records;       // 内存中的记录列表

public:
    Leaderboard();
    void load();                            // 从文件加载
    void save();                            // 保存到文件
    void add(std::wstring name, int coin);  // 添加新记录（会自动排序并保存）
    void draw(int x, int y);                // 在屏幕指定位置绘制排行榜
};