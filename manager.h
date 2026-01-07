#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<graphics.h>
#include<conio.h>
#include"button.h"

struct User {
	std::wstring username;
	std::wstring password;
	int coins;

	bool operator>(const User& other)const {
		return coins > other.coins;
	}
};

void save_coin_to_file(int coin);

