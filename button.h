#pragma once
#include<graphics.h>
#include<easyx.h>
#include<string>

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
    Button(int _x, int _y, int _w, int _h, const std::wstring& _text)
        : x(_x), y(_y), w(_w), h(_h), text(_text), pressed(false), hover(false),
        normalColor(LIGHTGRAY), hoverColor(WHITE), pressColor(LIGHTBLUE), textColor(BLACK) {
    }
    // 绘制按钮
    void draw() {
        COLORREF fill = normalColor;
        if (pressed) fill = pressColor;
        else if (hover) fill = hoverColor;

        setfillcolor(fill);
        fillrectangle(x, y, x + w, y + h);
        setlinecolor(BLACK);
        rectangle(x, y, x + w, y + h);

        setbkmode(TRANSPARENT);
        settextcolor(textColor);
		settextstyle(24, 0, L"宋体");
        int textW = textwidth(text.c_str());
        int textH = textheight(text.c_str());
        outtextxy(x + (w - textW) / 2, y + (h - textH) / 2, text.c_str());
    }

    // 更新状态，返回是否点击
    bool update(const MOUSEMSG& msg) {
        bool clicked = false;
        {
            int mx = msg.x, my = msg.y;
            hover = mx >= x && mx <= x + w && my >= y && my <= y + h;

            if (hover && msg.uMsg == WM_LBUTTONDOWN) pressed = true;
            if (pressed && msg.uMsg == WM_LBUTTONUP) {
                if (hover) clicked = true;
                pressed = false;
            }
        }
        return clicked;
    }
};
