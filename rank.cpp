#include "rank.h"

Leaderboard::Leaderboard() {
    load(); // 构造时自动加载数据
}

void Leaderboard::load() {
    records.clear();
    std::wifstream in(filename);
    // 设置本地化以支持读取文件中的非ASCII字符（如果在文件中存了中文）
    in.imbue(std::locale(""));

    if (!in.is_open()) return; // 如果文件不存在，直接返回

    PlayerRecord temp;
    // 简单的读取格式：名字 金币
    while (in >> temp.name >> temp.coins) {
        records.push_back(temp);
    }
    in.close();

    // 加载后再排一次序，保险
    std::sort(records.begin(), records.end(), std::greater<PlayerRecord>());
}

void Leaderboard::save() {
    std::wofstream out(filename);
    out.imbue(std::locale(""));

    for (const auto& rec : records) {
        // 写入格式：名字 空格 金币 换行
        out << rec.name << L" " << rec.coins << std::endl;
    }
    out.close();
}

void Leaderboard::add(std::wstring name, int coin) {
    PlayerRecord newRecord;
    newRecord.name = name;
    newRecord.coins = coin;

    records.push_back(newRecord);

    // 排序：从大到小
    std::sort(records.begin(), records.end(), std::greater<PlayerRecord>());

    // 如果超过10条，删除最后一名
    if (records.size() > MAX_RECORDS) {
        records.resize(MAX_RECORDS);
    }

    // 立即保存到文件
    save();
}

void Leaderboard::draw(int x, int y) {
    // 绘制半透明背景板 (可选)
    setfillcolor(BLACK);
    // solidrectangle(x - 10, y - 10, x + 250, y + 40 + records.size() * 30); 

    setbkmode(TRANSPARENT);
    settextcolor(YELLOW);
    settextstyle(24, 0, L"微软雅黑");

    outtextxy(x + 50, y, L"=== 排行榜 ===");

    settextcolor(WHITE);
    settextstyle(20, 0, L"宋体");

    for (int i = 0; i < records.size(); ++i) {
        wchar_t buf[128];
        // 格式化字符串： "1. 张三   Coin: 100"
        swprintf_s(buf, L"%d. %-10s  $%d", i + 1, records[i].name.c_str(), records[i].coins);

        // 前三名用不同颜色高亮
        if (i == 0) settextcolor(RGB(255, 215, 0));      // 金
        else if (i == 1) settextcolor(RGB(192, 192, 192)); // 银
        else if (i == 2) settextcolor(RGB(205, 127, 50));  // 铜
        else settextcolor(WHITE);

        outtextxy(x, y + 35 + i * 25, buf);
    }
}