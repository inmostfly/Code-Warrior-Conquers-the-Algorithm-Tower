#include "manager.h"
#include <fstream>

void save_coin_to_file(int coin) {
    std::ofstream fout("coin.txt", std::ios::app); // ×·¼ÓÐ´Èë
    fout << coin << std::endl;
}