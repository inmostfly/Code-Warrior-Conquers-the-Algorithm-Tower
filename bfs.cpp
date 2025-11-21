#pragma
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include "bfs.h"
#include "player.h"
#include "text_act.h"
#include "mapdata.h"
#include "button.h"
#include<string>

void enterBFSWindow(int map__bfs[Map::COL][Map::ROW],int type,int col,int row) {
    mciSendString(_T("close all"), NULL, 0, NULL);
    initmusic();
    mciSendString(_T("play bfsmusic repeat"), NULL, 0, NULL);
	//扩展性声明，在这里修改后续type就能得到不同的地图
    int choice = 0;
    initgraph(col*32, row*32); // 迷宫窗口尺寸

    step_max = 100;//重置最大步数限制
    Map Map_bfs;
    // 获取屏幕分辨率
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    // 计算居中位置
    int x = (screenW - col*32) / 2;
    int y = (screenH - row*32) / 2;
    // 获取窗口句柄并移动窗口
    HWND hwnd = GetHWnd();
    SetWindowPos(hwnd, HWND_TOP,x, y, 0, 0, TRUE);
    BeginBatchDraw();
    Button btnplay((col*32-300)/2, (row*32-60)/2-60, 300, 60, L"自行走动");
	Button btninput((col*32-300)/2, (row*32 - 60) / 2 + 60, 300, 60, L"输入结果走动");
    
    //player模块加载
    Player player;
    player.load();

    //map模块加载
    Map_bfs.Map_all(map__bfs, type);//初始化bfs地图
    Map_bfs.load(map__bfs);
    Map_bfs.draw(map__bfs);

    //text_act模块加载
    TextHint hint_bfs; // 创建提示对象
    hint_bfs.show_mind(L"欢迎进入bfs算法世界！", 60, (col*32), (row*32));//问题，提示词未做到居中显示
    FlushBatchDraw();
    //玩法选择
    while (choice == 0) {
        /*outtextxy(50, 20, L"玩法选择：");*/
        btnplay.draw();
        btninput.draw();
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (btninput.update(msg)) {
            choice = 2;
            break;
        }
            if (btnplay.update(msg)) {
            choice = 1;
            break;
        }
        }
        
        FlushBatchDraw();
		Sleep(10); // 控制帧率
    }

    if (choice == 2) {
        //输入结果控制走动
        TCHAR res[256];
		EndBatchDraw();
        SetForegroundWindow(GetHWnd());
        InputBox( res,256, L"请输入您的结果：", L"结果输入");
        std::wstring msg = L"您输入的结果为：" + std::wstring(res) + L",即将开始正确性检验!";
        MessageBox(GetHWnd(), msg.c_str(), L"正确性检验", MB_OK);
		player.setautomove(std::wstring(res)); // 设置自动移动指令
		BeginBatchDraw();
        while (player.autoMoving) {
            cleardevice();
            Map_bfs.draw(map__bfs);
            player.update(Map_bfs, map__bfs);
            player.draw();
			settextcolor(WHITE);
			wchar_t s[32];
			swprintf(s, 32, L"Last_step: %d", step_max);
            outtextxy(0, 0, s);
            hint_bfs.tick();
            hint_bfs.render(1);
            FlushBatchDraw();
            Sleep(20);
        }
        if (player.flag_win) {
            coin += type * 10 + step_max;
            wchar_t res[256];
			swprintf(res, 256, L"恭喜你完成此bfs关卡，您的剩余步数为:%d步，依照剩余步数获得金币奖励！是否要挑战更高难度关卡？", step_max);
			int res1=MessageBox(GetHWnd(), res, L"成功", MB_YESNO | MB_ICONQUESTION);
            {
                
                if (res1 == IDNO || type == 3) {
                    MessageBox(GetHWnd(), type==3?L"恭喜你已经完全掌握了BFS迷宫要领，请点击YES返回":L"请点击YES返回home!", L"congratulations!", MB_OK);
                    return;
                }
                else {
                    type++;
                    if (type == 2) {
                        enterBFSWindow(map_bfs, type, Map::x_bfs2, Map::y_bfs2); // 进入下一个BFS关卡
                        return;
                    }
                    else if (type == 3) {
                        enterBFSWindow(map_bfs, type, Map::x_bfs3, Map::y_bfs3); // 进入下一个BFS关卡
                        return;
                    }
                }
            }
        }
        else {
			int res2=MessageBox(GetHWnd(), L"很遗憾，您输入的路径未满足要求，是否要重新尝试？", L"失败", MB_YESNO|MB_ICONQUESTION);
            if (res2 == IDNO) {
				MessageBox(GetHWnd(), L"游戏即将结束！即将传送回home！", L"结束", MB_OK);
                return;
            }
            else {
				enterBFSWindow(map__bfs, type, col, row); // 重新进入BFS关卡
                return;
            }
        }
        return;
    }

    while (true) {
            cleardevice();
            Map_bfs.draw(map__bfs);
            player.update(Map_bfs,map__bfs);
            player.draw();    
            settextcolor(WHITE);
            wchar_t s[32];
            swprintf(s, 32, L"coin: %d", coin);
            outtextxy(0, 0, s);
            hint_bfs.tick();
            hint_bfs.render(1);
            FlushBatchDraw();
            // 处理事件
            // 到达终点
            int px = (player.x + 16) / 32;
            int py = (player.y + 16) / 32;
            if (map__bfs[py][px] == 9) {
				coin += type * 10; // 根据关卡类型奖励不同的金币
				int result = MessageBox(GetHWnd(), type!=3?L"恭喜你完成 BFS 关卡,请选择当前是否要挑战更高难度关卡？":L"恭喜你已经完全掌握了BFS迷宫要领，请点击YES返回", L"成功", MB_YESNO | MB_ICONQUESTION);
                if (result == IDNO || type == 3) {
                    MessageBox(GetHWnd(), L"恭喜你完成 BFS 关卡,获得金币奖励！即将传送回home！", L"成功", MB_OK);
					return ; // 退出循环，返回主界面
                }
                else {
                    type++;
                    if(type==2){
					enterBFSWindow(map_bfs, type, Map::x_bfs2, Map::y_bfs2); // 进入下一个BFS关卡
                    break;
                    //退出while循环
                    }
                    else if (type == 3) {
						enterBFSWindow(map_bfs, type, Map::x_bfs3, Map::y_bfs3); // 进入下一个BFS关卡
                        break;
                        //退出while循环
                    }
                }
            } 
            
           
           
            Sleep(20); // 控制帧率 
    } 
            EndBatchDraw();
}
  