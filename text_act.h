#pragma once
#include <string>

// 文本提示模块：用于游戏中的临时文字显示（事件提示、对话等）
class TextHint {
public:
    std::wstring message;  // 显示内容
    int frameLeft=0;         // 剩余帧数
    int posX, posY;        // 显示位置
    int fontSize;          // 字体大小
	bool flag = true; // 控制是否显示
public:
    TextHint();

    // 显示一条提示信息
    void show_mind(const std::wstring& msg, int duration = 180, int x = 280, int y = 200, int size = 24);
    void show_org(const std::wstring& msg, int duration = 180, int x = 280, int y = 200, int size = 24);
    // 每帧调用一次，减少计时
    void tick();

    // 每帧调用一次，渲染提示文本
    void render(int choice);

    // 是否仍在显示中
    bool isActive() const;
};
