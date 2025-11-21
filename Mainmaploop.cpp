#pragma once

#include "text_act.h"
#include "map.h"
#include "player.h"
#include "notice.h"
#include "bfs.h"
#include "mapdata.h"

void Mainmaploop() {
    mciSendString(_T("close all"), NULL, 0, NULL);
    initmusic();
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
    int xx =Map::x_org * 32;
    int yy =Map::y_org * 32;
    initgraph(xx, yy);
	setbkmode(TRANSPARENT);
    // 获取屏幕分辨率
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    // 计算居中位置
    int xMain = (screenW - xx) / 2;
    int yMain = (screenH - yy) / 2;
    // 获取窗口句柄并移动窗口
    HWND hwnd = GetHWnd();
    SetWindowPos(hwnd, HWND_TOP,xMain, yMain, 0, 0, TRUE);

    BeginBatchDraw();
    //player模块加载
    Player player;
    player.load();
    //map模块加载
    Map map;
    map.Map_all(map_org, 0);//初始化
    map.load(map_org);
    map.draw(map_org);


    //函数声明部分

    //text_act模块加载
    TextHint hint; // 创建提示对象

    hint.show_mind(L"欢迎进入算法世界！", 60,xx, yy);
    g_flag = false;
    while (true) {
        cleardevice();  
        setbkmode(TRANSPARENT);
        map.draw(map_org);
        player.update(map, map_org);
        player.draw();
        hint.tick();
        hint.render(1);
        coin_count++;
        fire_count++;
        settextcolor(WHITE);
        wchar_t s[32];
        swprintf(s, 32, L"coin: %d", coin);
        outtextxy(0, 0, s);
        FlushBatchDraw();//刷新绘图缓冲区，一次性显示
        Sleep(13);  // 控制帧率
        // 处理事件
        if (g_flag == true) {
            break;
        }
    }
    EndBatchDraw();
}
