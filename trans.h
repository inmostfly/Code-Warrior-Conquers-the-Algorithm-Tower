#pragma once
#include <graphics.h>
#include "text_act.h"
#include <windows.h>
#include "map.h"
#include "player.h"
#include "notice.h"
#include "bfs.h"
#include "mapdata.h"
extern int coin_count;
extern int fire_count;
void transport_begin(int map__transport[Map::COL][Map::ROW]);
