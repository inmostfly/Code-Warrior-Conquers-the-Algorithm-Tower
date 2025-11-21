#include "transport.h"
#include <stdlib.h>
#include <stdio.h>

//#define N 13
//#define M 78

// 迷宫地图，直接在代码里生成


//// 传送门链表头指针
//PortalNode* portalListHead = NULL;
//
//// 添加一个传送门节点（自动配对）
//void addPortal(char symbol, int x, int y) {
//    PortalNode* node = (PortalNode*)malloc(sizeof(PortalNode));
//    node->symbol = symbol;
//    node->x = x;
//    node->y = y;
//    node->pair = NULL;
//    node->prev = NULL;
//    node->next = portalListHead;
//    if (portalListHead) portalListHead->prev = node;
//    portalListHead = node;
//
//    // 查找是否已有配对
//    PortalNode* cur = portalListHead->next;
//    while (cur) {
//        if (cur->symbol == symbol) {
//            node->pair = cur;
//            cur->pair = node;
//            break;
//        }
//        cur = cur->next;
//    }
//}
//
//// 查找配对传送门（返回同字母但不同坐标的节点）
//PortalNode* findPair(char symbol, int x, int y) {
//    PortalNode* cur = portalListHead;
//    while (cur) {
//        if (cur->symbol == symbol && (cur->x != x || cur->y != y)) {
//            return cur;
//        }
//        cur = cur->next;
//    }
//    return NULL;
//}
//
//// 清空所有传送门节点
//void clearPortals() {
//    PortalNode* cur = portalListHead;
//    while (cur) {
//        PortalNode* next = cur->next;
//        free(cur);
//        cur = next;
//    }
//    portalListHead = NULL;
//}
//
//// 自动注册所有传送门
//void registerPortals() {
//    clearPortals();
//    for (int i = 0; i < N; ++i)
//        for (int j = 0; j < M; ++j)
//            if (maze[i][j] >= 'A' && maze[i][j] <= 'Z')
//                addPortal(maze[i][j], i, j);
//}
//
//
//void transport_main() {
//    registerPortals();
//    demoPlayerMove();
//    clearPortals();
//    return 0;
//}
void transport_begin(int map__transport[Map::COL][Map::COL]) {
	int col = 40, row = 15;
	initgraph(col * 32, row * 32); // 传送门窗口尺寸
    int blockSize = 40;
    IMAGE wallImg, floorImg, playerImg, endImg;

    Map Map_transport;
    // 获取屏幕分辨率
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    // 计算居中位置
    int x = (screenW - col * 32) / 2;
    int y = (screenH - row * 32) / 2;
    // 获取窗口句柄并移动窗口
    HWND hwnd = GetHWnd();
    SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, TRUE);
    BeginBatchDraw();

    //player模块加载
    Player player;
    player.load();

    //map模块加载
    Map_transport.Map_all(map__transport, 4);//初始化bfs地图
    Map_transport.load(map__transport);
    Map_transport.draw(map__transport);

    //text_act模块加载
    TextHint hint_tran; // 创建提示对象
    hint_tran.show_mind(L"欢迎进入链表的世界！", 60, (col * 32), (row * 32));//问题，提示词未做到居中显示
    

    while (true) {
        cleardevice();
        Map_transport.draw(map__transport);
        player.update(Map_transport, map__transport);
        player.draw();
        hint_tran.tick();
        hint_tran.render(1);
        // 处理事件
        // 到达终点
        int px = (player.x + 16) / 32;
        int py = (player.y + 16) / 32;
        //等待添加传送门事件
        FlushBatchDraw();
        Sleep(20); // 控制帧率 
    }
}
