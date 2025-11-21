#include "greedy.h"

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
    
    TextHint hint_greedy;
    hint_greedy.show_mind(L"欢迎进入贪心算法世界！", 60, (col * 32), (row * 32));
    FlushBatchDraw();
    while (true) {
        cleardevice();
		settextcolor(WHITE);
        Map_greedy.draw(map_greedy);
        player.update(Map_greedy, map_greedy);
        player.draw();
        hint_greedy.tick();
        hint_greedy.render(1);
        wchar_t s[32];
        swprintf(s, 32, L"coin: %d", coin);
        outtextxy(0, 0, s);
		int px = (player.x + 16) / 32;
		int py = (player.y + 16) / 32;
        FlushBatchDraw();
        Sleep(20);
    }
    EndBatchDraw();
}