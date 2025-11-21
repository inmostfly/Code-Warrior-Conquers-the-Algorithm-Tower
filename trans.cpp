#include "transport.h"
#include <graphics.h>
#include "map.h"
#include "player.h"
#include "text_act.h"
#include"mapdata.h"

// 传送门节点结构
struct PortalNode {
    char symbol; // 字母
    int x, y;    // 坐标
    PortalNode* pair; // 配对节点
    PortalNode* prev;
    PortalNode* next;
};
PortalNode* portalListHead = nullptr;

// 添加一个传送门节点（自动配对）
void addPortal(char symbol, int x, int y) {
    PortalNode* node = new PortalNode{symbol, x, y, nullptr, nullptr, portalListHead};
    if (portalListHead) portalListHead->prev = node;
    portalListHead = node;
    // 查找是否已有配对
    for (PortalNode* cur = portalListHead->next; cur; cur = cur->next) {
        if (cur->symbol == symbol) {
            node->pair = cur;
            cur->pair = node;
            break;
        }
    }
}

// 查找配对传送门（返回同字母但不同坐标的节点）
PortalNode* findPair(char symbol, int x, int y) {
    for (PortalNode* cur = portalListHead; cur; cur = cur->next) {
        if (cur->symbol == symbol && (cur->x != x || cur->y != y)) {
            return cur;
        }
    }
    return nullptr;
}



// 自动注册所有传送门
void registerportals(int map[Map::ROW][Map::COL]) {
    /*clearPortals();*/
    for (int i = 0; i < Map::ROW; ++i)
        for (int j = 0; j < Map::COL; ++j)
            if (map[i][j] >= 65 && map[i][j] <= 90)
                addPortal((char)map[i][j], i, j);//强制类型转换，亦可存int类型
}

int last_px=0, last_py=0;
void transport_begin(int map__transport[Map::ROW][Map::COL]) {
    int col = 39, row = 15;
    
    mciSendString(_T("close all"), NULL, 0, NULL);
    initmusic();
    mciSendString(_T("play dinomusic repeat"), NULL, 0, NULL);
    int blockSize = 40;
    Map Map_transport;
    // 获取屏幕分辨率
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    // 计算居中位置
    int x = (screenW - col * 32) / 2;
    int y = (screenH - row * 32) / 2;
    initgraph(col * 32, row * 32); // 传送门窗口尺寸
    // 获取窗口句柄并移动窗口
    HWND hwnd = GetHWnd();
    SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, TRUE);
    BeginBatchDraw();

    //player模块加载
    Player player;
    player.x = 50;
    player.y = 50;
    player.load();

    //map模块加载
    Map_transport.Map_all(map__transport, 4);//初始化bfs地图
    Map_transport.load(map__transport);
    Map_transport.draw(map__transport);

    //text_act模块加载
    TextHint hint_tran; // 创建提示对象
    hint_tran.show_mind(L"欢迎进入链表的世界！", 60, (col * 32), (row * 32));//居中显示
    TextHint hint_gift;
    hint_gift.show_mind(L"链表在内存中不连续，我们只有借助传送门\n即设置指向性指针，指向它所在的位置才能得以访问！", 200, col * 32, row * 32);
   

    registerportals(map__transport);//传送门注册
    int count = 0;

    while (true) {
        cleardevice();
        count++;
        if (count % 5 == 0) {
            trans_count++;
        }
        Map_transport.draw(map__transport);
        player.update(Map_transport, map__transport);
        player.draw();
        hint_tran.tick();
        hint_tran.render(1);
        // 处理事件
        // 到达终点
        int py = (player.x + 16) / 32;//屏幕x,矩阵y,px实际上就是矩阵的y
		int px = (player.y + 16) / 32;//屏幕y,矩阵x,py实际上就是矩阵的x
        int flag = 1;//flag作为是否重复传送的重要标志
        if (py == last_py &&px == last_px) {
            flag = 0;
        }
        last_px = px;
        last_py = py;//记录上一次的位置，如果没有移动就不要传送
        if (map__transport[px][py] >= 65 && map__transport[px][py] <= 90&&flag==1) {
             // 找到配对传送门
            
            PortalNode* pair = findPair((char)map__transport[px][py], px, py);
            if (pair) {
                mciSendString(_T("close transdoormusic"), NULL, 0, NULL);
				mciSendString(_T("open ./asset/transdoor.mp3 alias transdoormusic"), NULL, 0, NULL);
                mciSendString(_T("play transdoormusic"), NULL, 0, NULL);
                
                player.x = pair->y * 32; // 更新玩家位置
				player.y = pair->x * 32;//插入的时候我们是按照x,y来插入的，所以这里要交换
                last_px = pair->x;//同理，我们插入的时候是x,y
				last_py = pair->y; // 更新上次位置
                // 显示提示
                hint_tran.show_mind(L"传送成功！", 60, (col * 32), (row * 32));
            } 
        }
        if (map__transport[px][py] == -2) {
            MessageBox(GetHWnd(), L"恭喜完成链表传送关卡，获得金币奖励，即将传送回home!", L"Congratulations!", MB_OK);
            break;//退出该关卡
        }
        if (map__transport[px][py] == -41) {
			hint_gift.render(1);
        }
        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        wchar_t s1[32];
        swprintf(s1, 32, L"coin: %d", coin);
        outtextxy(0, 0, s1);
        //等待添加传送门事件
        coin_count++;
        FlushBatchDraw();
        Sleep(20); // 控制帧率 
    }
}
