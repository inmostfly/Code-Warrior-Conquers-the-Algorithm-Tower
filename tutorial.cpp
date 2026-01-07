#include "tutorial.h"

pair<int, int> randxy() // 作为初始值
{
	int x = rand() % MAP_COL + 1;
	int y = rand() % MAP_ROW + 1;
	return make_pair(x, y);
}

void initmap(int m[MAP_ROW + 5][MAP_COL + 5]) // 初始化地图
{
	for (int i = 1; i <= IMPASS_NUM; i++)
	{
		pair<int, int> p = randxy();
		m[p.second][p.first] = IMPASS;
	}
}

void rebackmap(int m[MAP_ROW + 5][MAP_COL + 5]) // 回溯整张地图
{
	for (int i = 1; i <= MAP_ROW; i++)
		for (int j = 1; j <= MAP_COL; j++)
			if (m[i][j] != IMPASS) m[i][j] = PASS;
}

void printmap(int m[MAP_ROW + 5][MAP_COL + 5]) // 输出地图
{
	for (int i = 1; i <= MAP_ROW; i++)
	{
		for (int j = 1; j <= MAP_COL; j++)
		{
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void paintrect(rect r) // 绘画一个矩形
{
	setfillcolor(r.color);
	fillrectangle(r.x, r.y, r.x + SIDE_LENGTH, r.y + SIDE_LENGTH);
}

void paintbutton(button bt) // 绘画一个按钮
{
	BeginBatchDraw();
	setlinestyle(PS_SOLID, 5);
	setlinecolor(BLACK);
	setfillcolor(bt.color);
	settextcolor(BLACK);
	settextstyle(70, 50, L"黑体");
	fillroundrect(bt.x, bt.y, bt.x + bt.w, bt.y + bt.h, 10, 10);
	int xx = bt.x + (bt.w - textwidth(bt.text)) / 2;
	int yy = bt.y + (bt.h - textheight(bt.text)) / 2;
	outtextxy(xx, yy, bt.text);
	EndBatchDraw();
}

// 改为接受 MOUSEMSG
bool isbuttondown(button bt, MOUSEMSG m) // 判断点击是否在按钮内
{
	if (m.x >= bt.x && m.x <= bt.x + bt.w && m.y >= bt.y && m.y <= bt.y + bt.h)
		return true;
	return false;
}

void paintmap(int m[MAP_ROW + 5][MAP_COL + 5]) {
	int mapx = (WINDOW_WIDTH - MAP_WIDTH) / 2; // 地图左上角的 x
	int mapy = (WINDOW_HEIGHT - MAP_HEIGHT) / 2; // 地图左上角的 y
	BeginBatchDraw();
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID);
	for (int i = 1; i <= MAP_ROW; i++){
		for (int j = 1; j <= MAP_COL; j++){
			rect tmp;
			switch (m[i][j])
			{
			case PASS:
				tmp = { mapx + (j - 1) * SIDE_LENGTH, mapy + (i - 1) * SIDE_LENGTH, GREEN };
				paintrect(tmp);
				break;
			case IMPASS:
				tmp = { mapx + (j - 1) * SIDE_LENGTH, mapy + (i - 1) * SIDE_LENGTH, BLACK };
				paintrect(tmp);
				break;
			case VISITED:
				tmp = { mapx + (j - 1) * SIDE_LENGTH, mapy + (i - 1) * SIDE_LENGTH, RED };
				paintrect(tmp);
				break;
			case VISITING:
				tmp = { mapx + (j - 1) * SIDE_LENGTH, mapy + (i - 1) * SIDE_LENGTH, RED };
				paintrect(tmp);
				break;
			default:
				break;
			}
		}
	}
	EndBatchDraw();
}

int nxt[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void dfs(int m[MAP_ROW + 5][MAP_COL + 5], int x, int y) // 深搜模拟
{
	settextstyle(70, 50, L"黑体");
	settextcolor(BLACK);
	outtextxy(0, WINDOW_HEIGHT / 3, L"DFS");
	paintmap(m);
	printmap(m);
	Sleep(DELAYTIME);
	for (int i = 0; i < 4; i++)
	{
		int xx = x + nxt[i][0];
		int yy = y + nxt[i][1];
		if (xx<1 || xx>MAP_ROW || yy<1 || yy>MAP_COL || m[xx][yy]) continue;
		m[xx][yy] = VISITING;
		dfs(m, xx, yy);
	}
	m[x][y] = VISITED;
}

void bfs(int m[MAP_ROW + 5][MAP_COL + 5], int x, int y) // 广搜模拟
{
	queue<pair<int, int> > Q;
	Q.push(make_pair(x, y));
	m[x][y] = VISITING;
	while (!Q.empty())
	{
		pair<int, int> a = Q.front();
		Q.pop();
		settextstyle(70, 50, L"黑体");
		settextcolor(BLACK);
		outtextxy(0, WINDOW_HEIGHT / 3, L"BFS");
		paintmap(m);
		printmap(m);
		m[a.first][a.second] = VISITED;
		Sleep(DELAYTIME);
		for (int i = 0; i < 4; i++)
		{
			int xx = a.first + nxt[i][0];
			int yy = a.second + nxt[i][1];
			if (xx<1 || xx>MAP_ROW || yy<1 || yy>MAP_COL || m[xx][yy]) continue;
			Q.push(make_pair(xx, yy));
			m[xx][yy] = VISITING;
		}
	}
}

void tutorial() // 主函数
{
	int map[MAP_ROW + 5][MAP_COL + 5];
	int step = 1;
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);
	int xMain = (screenW - WINDOW_WIDTH) / 2;
	int yMain = (screenH - WINDOW_HEIGHT) / 2;

	srand((unsigned)time(NULL)); 

	// 地图初始化
	memset(map, PASS, sizeof(map));
	initmap(map);
	printmap(map);

	// 窗口初始化
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice(); // 清屏
	HWND hwnd = GetHWnd();
	SetWindowPos(hwnd, HWND_TOP, xMain, yMain, 0, 0, TRUE);
	// 主界面按钮
	button b1 = { (WINDOW_WIDTH - 2 * BUTTON_WIDTH - BUTTON_INTERVAL) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT, L"DFS", WHITE };
	button b2 = { (WINDOW_WIDTH + BUTTON_INTERVAL) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT, L"BFS", WHITE };
	Button EXIT(WINDOW_WIDTH-100, 100, 50, 30, L"退出");
	pair<int, int> p = randxy(); // 生成随机起点

	// 消息循环
	while (true)
	{
		if (step == 1) // 处于主界面阶段绘制按钮
		{
			paintbutton(b1);
			paintbutton(b2);
			EXIT.draw();
		}

		// 使用一致的 MOUSEMSG 处理
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			switch (m.uMsg) {
			case WM_LBUTTONDOWN:// 鼠标左键按下
				if (step != 1) break; // 不在主界面时跳过
				if (isbuttondown(b1, m))
				{
					step = 2; // 进入dfs搜索阶段
					cleardevice();
					rebackmap(map);
					map[p.second][p.first] = VISITING;
					dfs(map, p.second, p.first);
					Sleep(1000);
					cleardevice();
					step = 1; // 回到主界面
				}
				else if (isbuttondown(b2, m))
				{
					step = 2; // 进入bfs搜索阶段
					cleardevice();
					rebackmap(map);
					bfs(map, p.second, p.first);
					Sleep(1000);
					cleardevice();
					step = 1; // 回到主界面
				}
				else if (EXIT.update(m)) {
					closegraph();
					return;
				}
				break;
			case WM_MOUSEMOVE:
				if (step != 1) break; // 不在主界面时跳过
				if (isbuttondown(b1, m))
				{
					b1.color = YELLOW;
					paintbutton(b1);
				}
				else
				{
					b1.color = WHITE;
					paintbutton(b1);
				}
				if (isbuttondown(b2, m))
				{
					b2.color = YELLOW;
					paintbutton(b2);
				}
				else
				{
					b2.color = WHITE;
					paintbutton(b2);
				}
				break;
			}
		}
	}
	closegraph();
	return;
}