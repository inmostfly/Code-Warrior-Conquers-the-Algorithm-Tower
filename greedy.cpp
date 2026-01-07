#include "greedy.h"

extern int coin; //仍然是全局

int capacity;

void greedy_begin(int map_greedy[Map::ROW][Map::COL],int type,int col,int row) {
    mciSendString(_T("close all"), NULL, 0, NULL);
    initmusic();
    mciSendString(_T("play bfsmusic repeat"), NULL, 0, NULL);
    
	initgraph(col * 32, row * 32); // 贪心窗口尺寸
    Map Map_greedy;

	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);

    int y = (screenH - row * 32) / 2;
    int x = (screenW - col * 32) / 2;
    HWND hwnd = GetHWnd();
	SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, TRUE);
    BeginBatchDraw();

    Player player;
    player.load();
    
	Map_greedy.Map_all(map_greedy, type);//初始化贪心地图
    Map_greedy.load(map_greedy);
	Map_greedy.draw(map_greedy);

    struct Item { 
        int w; 
        int v; 
    };
    std::vector<Item> items; // 对于 0-1 背包, 每个宝箱位置视为一个独立物品
    std::map<int, Item> typeMap;

    typeMap[104] = {3, 10};
    typeMap[105] = {5, 18};
    typeMap[106] = {8, 30};

    // 扫描地图取得宝箱信息
    for (int i = 0; i < Map::ROW; ++i) {
        for (int j = 0; j < Map::COL; ++j) {
            int v = map_greedy[i][j];
            if (v >= 101 && v <= 199) {
                if (type == 9) {
                    // normal: 不完全背包（这里实现为完全背包）
                    // 将箱子类型加入 typeMap 已足够
                } else if (type == 10) {
                    // hard: 0-1 背包，地图上每个箱子视为独立物品
                    int key = v;
                    if (typeMap.count(key)) items.push_back(typeMap[key]);
                    else {
                        items.push_back({2,5});
                    }
                } else if (type == 8) {
                    int key = v;
                    if (typeMap.count(key)) items.push_back(typeMap[key]);
                }
            }
        }
    }

    capacity = 35;

    int bestValue = 0;
    std::vector<int> chosenCounts;

    if (type == 9) {
        // normal我们实现为完全背包示例
        // 使用 type中的物品种类进行完全背包 DP
        std::vector<int> dp(capacity+1, 0);
        for (auto &kv : typeMap) {
            int wt = kv.second.w, val = kv.second.v;
            for (int w = wt; w <= capacity; ++w) {
                dp[w] = dp[w]>(dp[w - wt] + val)?dp[w]:(dp[w - wt] + val);
            }
        }
        bestValue = dp[capacity];
    } else {

        int n = (int)items.size();
        std::vector<int> dp(capacity+1, 0);
        for (int i = 0; i < n; ++i) {
            int wt = items[i].w, val = items[i].v;
            for (int w = capacity; w >= wt; --w) {
                dp[w] = dp[w] > (dp[w - wt] + val) ? dp[w] : (dp[w - wt] + val);
            }
        }
        bestValue = dp[capacity];
    }

    TextHint hint_greedy;
    hint_greedy.show_mind(L"欢迎进入0-1背包算法世界！", 60, (col * 32), (row * 32));
    FlushBatchDraw();
    if (bestValue > 0) {
        coin += bestValue;
        wchar_t msg[256];
        swprintf(msg, 256, L"背包优化完成！最佳价值: %d，奖励已发放。", bestValue);
        MessageBox(GetHWnd(), msg, L"背包算法结果", MB_OK);
    } else {
        MessageBox(GetHWnd(), L"当前无可用物品或背包容量不足，未获得奖励。", L"背包算法结果", MB_OK);
    }

    while (true) {
        cleardevice();
		settextcolor(WHITE);
        Map_greedy.draw(map_greedy);
        fire_count++;
        player.update(Map_greedy, map_greedy);
        player.draw();
        hint_greedy.tick();
        hint_greedy.render(1);
        wchar_t s[32];
        swprintf(s, 32, L"coin: %d", coin);
        outtextxy(0, 0, s);
		int px = (player.x + 16) / 32;
		int py = (player.y + 16) / 32;
        if (map_greedy[py][px] == -2) {
			MessageBox(GetHWnd(), L"恭喜你完成此背包关卡！奖励已发放，请点击YES返回home！", L"Congratulations!", MB_OK);
            return;
        }
        FlushBatchDraw();
        Sleep(20);
    }
    EndBatchDraw();
}