#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <vector>
#include <stdio.h>
#include <algorithm>
#include "stdintdef.hpp"

class Maze{
    public:
    
    /**
     * @brief スタート座標を設定する。複数設定可能。
     * 
     */
    std::vector< std::vector<uint8_t>> start{{0, 0}};
    
    /**
     * @brief ゴール座標を設定する。複数設定可能。
     * 
     */
    //std::vector< std::vector<uint8_t>> goal{{7, 7}, {7, 8}, {8, 7}, {8, 8}};
    std::vector< std::vector<uint8_t>> goal{{3, 3}};

    /**
     * @brief 二進数で↓←→↑
     * 
     */
    uint8_t wall[16][16] = {};
    
    static const uint8_t IS_SEARCHED = 0b00010000;

    /**
     * @brief 各区画のコスト
     * 
     */
    uint8_t cost[16][16] = {};

    /**
     * @brief 進める向き。二進数で↓←→↑
     * 
     */
    uint8_t route[16][16] = {};

    Maze();

    void wall_update(uint8_t x, uint8_t y, uint8_t w);

    

};

#endif