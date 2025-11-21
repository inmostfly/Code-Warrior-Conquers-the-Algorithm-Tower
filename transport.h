#pragma once
#include <graphics.h>
#include "text_act.h"
#include <windows.h>
#include "map.h"
#include "player.h"
#include "notice.h"
#include "bfs.h"
#include "mapdata.h"
//typedef struct PortalNode {
//    char symbol;           // 传送门字母
//    int x, y;              // 坐标
//    struct PortalNode* pair; // 指向配对的传送门
//    struct PortalNode* prev;
//    struct PortalNode* next;
//} PortalNode;
//
//// 传送门链表头
//extern PortalNode* portalListHead;
//
//// 添加传送门节点
//void addPortal(char symbol, int x, int y);
//
//// 查找传送门配对
//PortalNode* findPair(char symbol, int x, int y);
//
//void transport_main();
//
//// 清空链表
//void clearPortals();

void transport_begin(int map__bfs[Map::COL][Map::COL]);