#include "dino_game.h"
#include"imageload.h"
#include "text_act.h"
#include "button.h"
void runDinoGame() {
    mciSendString(_T("close all"), NULL, 0, NULL);
    initmusic();
    mciSendString(_T("play dinomusic repeat"), NULL, 0, NULL);
    // 初始化随机数
    srand((unsigned)time(NULL));
   
    // 创建独立窗口（分辨率可调）
    initgraph(800, 300);
    cleardevice();
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH= GetSystemMetrics(SM_CYSCREEN);
    int xMain = (screenW - 800) / 2;
    int yMain = (screenH - 300) / 2;
    // 获取窗口句柄并移动窗口
    HWND hwnd = GetHWnd();
    SetWindowPos(hwnd, HWND_TOP,xMain, yMain, 0, 0, TRUE);
	setbkcolor(WHITE);
    // 恐龙
    Dino dino = { 100, 200, 0, false, 32, 32 };
    IMAGE dinoImg;
    IMAGE birdImg1;
    IMAGE birdImg2;

    // 地面
    int groundY = 200;

    // 障碍物
    Obstacle obs;
    Bird bird;

    obs.w = 25;
    obs.h = 44;
    obs.x = 800;
    obs.y = groundY; // 贴地
    obs.passed = false;

    bird.w = 46;
    bird.h = 32;
    bird.x = 600;
    bird.y = 100;
    bird.passed = false;
    loadimage(&birdImg1, L"asset/bird1.png",bird.w,bird.h,true);
    loadimage(&birdImg2, L"asset/bird2.png",bird.w,bird.h,true);
    BeginBatchDraw();
    IMAGE obsImg;
    loadimage(&obsImg, L"asset\\obstacle.jpg", obs.w, obs.h);

    // 物理参数
    double gravity = 1.0;
    double jumpPower = -15;
    int score = 0;
    int speed = 5;
    int birdframe = 0;
    int dinoframe = 0;//dino帧率切换
    int frame = 0;
    //文字提示模块
    TextHint hint_score;
    TextHint hint_speed;
    TextHint hint_begin;
    hint_begin.show_mind(L"冒险家！尽可能取得更高的分数！", 1, 700, 200, 24);
	hint_speed.show_mind(L"速度提升", 0,700, 200, 24);
    //按钮模块
    Button startbtn((800-150)/2,(300-50)/2,150, 50, L"开始游戏");
    startbtn.normalColor = RGB(100, 150, 200);
    while (TRUE) {
        cleardevice();
        setbkcolor(WHITE);
        hint_begin.render(2);
        MOUSEMSG msg=GetMouseMsg();
        if (startbtn.update(msg)) {
            break;
        }
        startbtn.draw();
        FlushBatchDraw();
        Sleep(10);
    }
    loadimage(&dinoImg, L"asset/player.png", 96, 128, true);
    while (TRUE) {
        frame++;
        cleardevice();
        if (frame % 5 == 0) {
            birdframe++;
        }
        if (frame % 2 == 0) {
            dinoframe++;
        }
        dinoframe = dinoframe % 3;
        birdframe = birdframe % 2;
		/*std::wstring dinoPath = L"D:\\Users\\12298\\Desktop\\MYCODE_test\\dino" + std::to_wstring(dinoframe) + L".png";*/
        
        // 绘制地面
        setlinecolor(BLACK);
        line(0, groundY + dino.h, 800, groundY + dino.h);
		setbkmode(TRANSPARENT);
        // 输入
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState('W') & 0x8000) && !dino.jumping) {
            dino.vy = jumpPower;
            dino.jumping = true;
        }

        // 更新恐龙
        dino.y += dino.vy;
        dino.vy += gravity;
        if (dino.y >= groundY) {
            dino.y = groundY;
            dino.vy = 0;
            dino.jumping = false;
        }
        if (frame % 800 == 0 && score != 0) {
            speed++;
            hint_speed.frameLeft = 100;
        }
        hint_speed.render(3);
        hint_speed.tick();
        if (frame % 100 == 0 && score != 0) {
            coin++;
        }
        // 更新障碍物
        obs.x -= speed;
        bird.x -= speed*2;
        if (obs.x < 0) {
            obs.x = 800 + 200 + rand() % 300; // 随机间距
            obs.passed = false;
        }
        if (bird.x < 0) {
            bird.x = 800 + rand() % 600 + 300;
            bird.y = 80 + rand() % 100;
            bird.passed = false;
        }
        
        // 加分 + 提速
        if (obs.passed == false && dino.x > obs.x) {
            score++;
            obs.passed = true;
        }
        if (bird.passed == false && dino.x > bird.x) {
            score++;
            bird.passed = true;
        }
        // 碰撞检测
        if (dino.x < obs.x + obs.w && dino.x + dino.w > obs.x &&
            dino.y < obs.y + obs.h && dino.y + dino.h > obs.y||dino.x<bird.x+bird.w&&dino.x+dino.w>bird.x&&dino.y<bird.y+bird.h&&dino.y+dino.h>bird.y) {
            MessageBox(GetHWnd(), L"游戏结束！", L"提示", MB_OK);
            break;
        }


        // 绘制恐龙
        putimage_alpha_clip(dino.x, dino.y,dino.w,dino.h,&dinoImg,dinoframe*32,64);
        // 调试 hitbox：
        // fillrectangle(dino.x, dino.y, dino.x + dino.w, dino.y + dino.h);

        // 绘制障碍物
        putimage_alpha_clip(obs.x, obs.y,obs.w,obs.h,&obsImg,0,0);
        // fillrectangle(obs.x, obs.y, obs.x + obs.w, obs.y + obs.h);
        if(birdframe%2==0)
            putimage_alpha_clip(bird.x, bird.y, bird.w, bird.h, &birdImg1, 0, 0);
        else {
            putimage_alpha_clip (bird.x, bird.y, bird.w, bird.h, &birdImg2, 0, 0);
        }
        //文字倒计时
        
        // 绘制分数
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        wchar_t s1[32];
        swprintf(s1, 32, L"分数: %d", score);
        outtextxy(10, 10, s1);

        settextcolor(BLACK);
        wchar_t s2[32];
        swprintf(s2, 32, L"coin:%d", coin);
        outtextxy(10, 50, s2);
        FlushBatchDraw();
        Sleep(23);
    }

    EndBatchDraw();
}
