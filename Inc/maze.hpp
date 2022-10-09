#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <cstdint>

class Maze{
    public:
    /**
     * @brief 二進数で↓←→↑
     * 
     */
    uint8_t wall[16][16];
    /**
     * @brief 各区画のコスト
     * 
     */
    uint8_t cost[16][16];

    void print();

};

#endif