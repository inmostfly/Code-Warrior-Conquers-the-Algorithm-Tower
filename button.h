#pragma once
#include<graphics.h>
#include<easyx.h>
#include<string>
#pragma comment(lib, "winmm.lib")
class Button {
public:
    int x, y, w, h;               // 按钮位置和大小
    std::wstring text;             // 按钮文字
    bool pressed;                  // 按钮是否被按下
    bool hover;                    // 鼠标是否悬停在按钮上
    COLORREF normalColor;          // 正常状态颜色
    COLORREF hoverColor;           // 悬停状态颜色
    COLORREF pressColor;           // 点击按下状态颜色
    COLORREF textColor;            // 文字颜色
    Button(int _x, int _y, int _w, int _h, const std::wstring& _text);
    // 绘制按钮
    void draw();

    // 更新状态，返回是否点击
    bool update(const MOUSEMSG& msg);
};
