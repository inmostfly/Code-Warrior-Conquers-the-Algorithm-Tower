#pragma
#include "text_act.h"
#include <graphics.h>
#include<sstream>
#include<vector>
TextHint::TextHint() {
    frameLeft = 0;
    posX = posY = 0;
    fontSize = 24;
}
// 显示一条提示信息，两种显示方法
void TextHint::show_mind(const std::wstring& msg, int duration, int x, int y, int size) {
    message = msg;
    frameLeft = duration;
    posX = x / 2;
	posY = y / 2; // 居中显示
    fontSize = size;
}
void TextHint::show_org(const std::wstring& msg, int duration, int x, int y, int size) {
    message = msg;
    frameLeft = duration;
    posX = x; // 原位置显示
    posY = y;
    fontSize = size;
    flag = true;
}

void TextHint::tick() {
    if (frameLeft > 0)
        frameLeft--;
}

void TextHint::render(int choice) {
    if (frameLeft > 0 && flag == true) {
        switch (choice) {
        case 1:settextcolor(WHITE); break;
        case 2:settextcolor(RED); break;
        case 3:settextcolor(BLACK); break;
        }

        setbkmode(TRANSPARENT);
        settextstyle(fontSize, 0, L"加粗字体");
     
        std::wstringstream wss(message);
        std::wstring line;
        std::vector<std::wstring> lines;
        while (std::getline(wss, line, L'\n')) {
            lines.push_back(line);
        }
        int lineHeight = textheight(L"A"); // 获取单行文本高度 
        int totalHeight = lineHeight * lines.size(); // 计算总高度
        int startY = posY - totalHeight / 2; // 实现垂直居中
        for (int i = 0; i < (int)lines.size(); i++) {
			int lineWidth = textwidth(lines[i].c_str());
			int startX = posX - lineWidth / 2; // 实现水平居中
            outtextxy(startX, startY + i * lineHeight, lines[i].c_str());
        }
    }
}

bool TextHint::isActive() const {
    return frameLeft > 0;
}
