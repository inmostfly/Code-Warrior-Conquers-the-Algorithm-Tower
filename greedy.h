#pragma once
#include "mapdata.h"
#include "player.h"
#include "bfs.h"
#include "text_act.h"
#include "button.h"
#include <algorithm>
#include<map>
#pragma comment(lib, "winmm.lib")
void greedy_begin(int map_greedy[Map::COL][Map::ROW], int type, int col, int row);