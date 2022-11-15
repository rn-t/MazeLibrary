#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <vector>
#include <stdio.h>
#include <algorithm>
#include "stdintdef.hpp"

class Maze{
    public:
    
    /**
     * @brief ゴール座標を保存する。コンストラクタで指定。
     * 
     */
    std::vector< std::vector<uint8_t>> start;
    
    /**
     * @brief ゴール座標を保存する。コンストラクタで指定。
     * 
     */
    std::vector< std::vector<uint8_t>> goal;

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

    Maze(std::vector< std::vector<uint8_t>> new_start, std::vector< std::vector<uint8_t>> new_goal);

    void wall_update(uint8_t x, uint8_t y, uint8_t w);

    

};

#endif