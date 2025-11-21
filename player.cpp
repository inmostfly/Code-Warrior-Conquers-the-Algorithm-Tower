#pragma once
#include "player.h"  
#include "easyx.h" // 添加此行以包含 EasyX 库头文件  
#include "bfs.h" // 添加此行以包含 BFS 头文件
#include "mapdata.h"
#include"dino_game.h"
#include"trans.h"
#include"greedy.h"
Player::Player() {  
    x = 96;  
    y = 96;  
    dir = 0;  
    frame = 0; 
    move_count = 0;
    step_num = 0;
    flag_win = false;
}  

void Player::load() {  
    loadimage(&sprite, L"asset/player.png",96,128);  
}  

// 更新玩家状态，走动来触发事件，并切换帧动画
void Player::update(Map& map, int temp[Map::ROW][Map::COL]) {
    int speed = 4;
    int newX = x, newY = y;
    int moved = false;
    if (autoMoving && !inputqueue.empty()) {
        if (!movingtonext) {
            currentcmd = inputqueue.front();
            inputqueue.pop();
            int tarx, tary;
            switch (currentcmd) {
            case 'W': dir = 3; targetx = x; targety = y - 32; break;
            case 'S': dir = 0; targetx = x; targety = y + 32; break;
            case 'A': dir = 1; targetx = x - 32; targety = y; break;
            case 'D': dir = 2; targetx = x + 32; targety = y; break;
            default:break; // 处理其他输入
            }
            movingtonext = true;
        }
        if (movingtonext) {
            move_count++;
            if (x < targetx) newX += speed;
            if (x > targetx) newX -= speed;
            if (y < targety) newY += speed;
            if (y > targety) newY -= speed;
            int ppx = (newX + 16) / 32, ppy = (newY + 16) / 32; // 计算角色中心点坐标

            if (map.isWalkable(ppx * 32, ppy * 32, temp)) {
                x = newX;
                y = newY;
                step_num++;
            }

            frame = (frame + 1) % 3;

            if (abs(x - targetx) < speed && abs(y - targety) < speed || move_count > 8) {
                movingtonext = false; // 到达目标位置后停止移动
                move_count = 0; // 重置移动计数
                step_max--;
            }
            if (temp[ppy][ppx] == 9) {
                flag_win = true;
                autoMoving = false; // 到达终点后停止自动移动

            }
            if (inputqueue.empty()) {
                if (temp[ppy][ppx] == 9) {
                    flag_win = true;
                }
                autoMoving = false;
            }
        }
        if (inputqueue.empty()) {
            autoMoving = false;
        }
        return;
    }
    moved = false;
    if (GetAsyncKeyState('W') & 0x8000) { dir = 3; newY -= 4; moved = true; }
    if (GetAsyncKeyState('S') & 0x8000) { dir = 0; newY += 4; moved = true; }
    if (GetAsyncKeyState('A') & 0x8000) { dir = 1; newX -= 4; moved = true; }
    if (GetAsyncKeyState('D') & 0x8000) { dir = 2; newX += 4; moved = true; }
    int px = (newX + 16) / 32, py = (newY + 16) / 32; // 计算角色中心点坐标  
    if (moved) {

        if (map.isWalkable(px * 32, py * 32, temp)) {
            x = newX; // 如果可以走，更新位置  
            y = newY;
        }
        frame = (frame + 1) % 3;
        //随机事件检测  
         // 事件触发（地图值为2,bfs事件）
        if (temp[py][px] / 10 == 2) {
            MessageBox(GetHWnd(), L"你触发了一个事件：请准备进入 BFS 算法闯关！", L"事件触发", MB_OK);
            g_flag = true;
            closegraph(); // 关闭当前窗口
            if (temp[py][px] == 21) {
                enterBFSWindow(map_bfs, 1, Map::x_bfs1, Map::y_bfs1); // 进入 BFS 关卡窗口
                return;
            }
            else if (temp[py][px] == 22) {
                enterBFSWindow(map_bfs, 2, Map::x_bfs2, Map::y_bfs2);
                return;
            }
            else if (temp[py][px] == 23) {
                enterBFSWindow(map_bfs, 3, Map::x_bfs3, Map::y_bfs3);
                /*coin += 30;*/
                return;
            }
            //return; // 事件触发后不再继续执行
        }
        if (temp[py][px] == 31) {
            g_flag = true;
            MessageBox(GetHWnd(), L"你遭遇到了二向箔打击，即将塌缩到二维世界！", L"事件触发", MB_OK);
            runDinoGame();
            return;
        }
        if (temp[py][px] == 32) {
            g_flag = true;
            MessageBox(GetHWnd(), L"你触发了一个事件：即将进入链表的世界！", L"事件触发", MB_OK);
            transport_begin(map_bfs); // 进入传送门窗口
            return;
        }
        if(temp[py][px]==41){
            g_flag = true;
            MessageBox(GetHWnd(), L"你触发了一个事件：即将进入背包特训关卡！", L"事件触发", MB_OK);
            greedy_begin(map_bfs,5,30,15); // 进入贪心窗口
            return;
		}
        if (temp[py][px] == 42) {
            g_flag = true;
            MessageBox(GetHWnd(), L"你触发了一个事件：即将进入不完全背包的世界！", L"事件触发", MB_OK);
            greedy_begin(map_bfs, 6, 30, 15); // 进入贪心窗口
            return;
        }
        if(temp[py][px] == 43) {
            g_flag = true;
            MessageBox(GetHWnd(), L"你触发了一个事件：即将进入0-1背包的世界！", L"事件触发", MB_OK);
            greedy_begin(map_bfs, 7, 30, 15); // 进入贪心窗口
            return;
		}
        if (temp[py][px] == -1) {//游戏出口
            g_flag = true;
            FLAG = 0;
            std::wstring msg = L"游戏结束，您的最终得分为" + std::to_wstring(coin);
            MessageBox(GetHWnd(), msg.c_str(), L"exit", MB_OK);
            return;
        }

        //链表模块，数字为3,触发金币拾取
        if (temp[py][px] == 3) {
            coin++;
            mciSendString(_T("close coinmusic"), NULL, 0, NULL);
            mciSendString(_T("open ./asset/coin.mp3 alias coinmusic"), NULL, 0, NULL);
            mciSendString(_T("play coinmusic"), NULL, 0, NULL);
            temp[py][px] = 0;
        }  
        if (temp[py][px] == 10) {
			int res=MessageBox(GetHWnd(), L"确认阅读README文档？", L"confirm", MB_YESNO);
			if (res == IDNO) return;
            else
		    ShellExecuteA(NULL, "open", "README.html", NULL,NULL, SW_SHOWNORMAL);
        }
        if (temp[py][px] == 101||temp[py][px]==102||temp[py][px]==103) {
            int res = MessageBox(GetHWnd(), L"确认领取迷宫结构图？",L"confirm", MB_YESNO);
            int tem = temp[py][px] % 100;
            std::string msg = "D:/Users/12298/Desktop/data_bfs/bfs_data" + std::to_string(tem) + ".txt";
            if (res == IDNO) return;
            else {
				ShellExecuteA(NULL, "open", msg.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }
        }
  
    }
    //"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe"
    //告示板模块，在这里与上方相反，只要不移动就会一直显示提示信息
    if (temp[py][px] == -31) {
        TextHint notice;
        notice.show_mind(L"轻松一下!前方为奇遇房间，你可以在这里赚取金币！", 200, Map::x_org * 32, Map::y_org * 32);
        notice.render(1);
    }
    if (temp[py][px] == -32) {
        TextHint notice;
        notice.show_mind(L"时间有限!请尽快抵达终点!", 200, 16 * 32, 10 * 32);
        notice.render(1);
    }
    if (temp[py][px] == -33) {
        TextHint notice;
        notice.show_mind(L"时间有限!请尽快抵达终点!", 200, 15 * 32, 11 * 32);
        notice.render(1);
    }
    if (temp[py][px] == -34) {
        TextHint notice;
        notice.show_mind(L"时间有限!请尽快抵达终点!", 200, 30 * 32, 19 * 32);
        notice.render(1);
    }
    if (temp[py][px] == -35) {
        TextHint notice;
        notice.show_mind(L"前方为bfs迷宫阵列，魔王为抵御我们取得勇者之剑,设下了重重限制!\n而值得庆幸的是,我们的先遣部队已经取得迷宫地图抽象矩阵\n分别存储在bfsdata1/2/3.txt文件中,三个文件分别存储在对应传送门旁边的宝箱内", 200, Map::x_org * 32, Map::y_org * 32);
        notice.render(1);
    }
    if (temp[py][px] == -37) {
        TextHint notice;
		notice.show_mind(L"前方为贪心与背包房间，不同金币有着不同的价值！\n请利用好有限的背包空间，尽可能多的囤积资源！\n最上方为特训关卡，在训练合格后你将获得真正进入宝库的资格！", 200, Map::x_org * 32, Map::y_org * 32);
        notice.render(1);
    }
    if (temp[py][px] == -38) {
        TextHint notice;        
        notice.show_mind(L"前方为特训关卡！\n加油！无畏的勇者！",200,Map::x_org*32,Map::y_org*32);
        notice.render(1);
    }
    if (temp[py][px] == -39) {
        TextHint notice;
		notice.show_mind(L"前方为不完全背包的宝库！\n请合理利用背包空间，争取获得最高的材料价值！", 200, Map::x_org * 32, Map::y_org * 32);
        notice.render(1);
    }
    if (temp[py][px] == -40) {
        TextHint notice;
		notice.show_mind(L"前方为完全背包的宝库！\n请合理利用背包资源，争取获得最高的宝物价值", 200, Map::x_org * 32, Map::y_org * 32);
        notice.render(1);
    }
    /*if(temp[py][px]==-36){
        TextHint notice;
		notice.show_mind(L"值得庆幸的是,我们的先遣部队已经取得迷宫地图抽象矩阵\n分别存储在bfsdata1/2/3.txt文件中,三个文件分别存储在对应传送门旁边的宝箱内", 200, Map::x_org * 32, Map::y_org * 32);
        notice.render(1);
	}*/
  
}

void Player::draw() {  
    int frameW = 32, frameH = 32;  
    int sx = frame * frameW;   // 0, 32, 64  
    int sy = dir * frameH;     // 0, 32, 64, 96  
    putimage_alpha_clip(x, y, frameW, frameH, &sprite, sx, sy);//在这里实现角色走动，切换帧动画  

}

void Player::setautomove(const std::wstring& input) {
    while (!inputqueue.empty()) inputqueue.pop();
    for (auto c : input) {
        if(c==L'W'||c==L'S' || c==L'A' || c==L'D') {
            inputqueue.push(char(c));
		}
    }
    inputqueue.push('Y');
    autoMoving = true;
    movingtonext = false;
}