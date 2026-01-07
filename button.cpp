#include"button.h"

Button::Button(int _x, int _y, int _w, int _h, const std::wstring& _text)
    : x(_x), y(_y), w(_w), h(_h), text(_text), pressed(false), hover(false),
    normalColor(LIGHTGRAY), hoverColor(WHITE), pressColor(LIGHTBLUE), textColor(BLACK) {
    }

void Button::draw() {
    COLORREF fill = normalColor;
    if (pressed) fill = pressColor;
    else if (hover) fill = hoverColor;
    setfillcolor(fill);
    fillrectangle(x, y, x + w, y + h);
    setlinecolor(BLACK);
    rectangle(x, y, x + w, y + h);

    setbkmode(TRANSPARENT);
    settextcolor(textColor);
    settextstyle(24, 0, L"ËÎÌו");
    int textW = textwidth(text.c_str());
    int textH = textheight(text.c_str());
    outtextxy(x + (w - textW) / 2, y + (h - textH) / 2, text.c_str());
}

bool Button::update(const MOUSEMSG& msg) {
    bool clicked = false;
    {
        int mx = msg.x, my = msg.y;
        hover = mx >= x && mx <= x + w && my >= y && my <= y + h;

        if (hover && msg.uMsg == WM_LBUTTONDOWN) {
            pressed = true;
            clicked = true;
        }

        //if (pressed && msg.uMsg == WM_LBUTTONUP) {
        //    if (hover) clicked = true;
        //    pressed = false;
        //}
    }
    return clicked;
}