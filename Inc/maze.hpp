#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <cstdint>


class Maze{
    public:
    
    /**
     * @brief ゴール座標の左下を設定する。2x2のゴールを仮定している。
     * 
     */
    const uint8_t goal[2] = {7, 7};

    /**
     * @brief 二進数で↓←→↑
     * 
     */
    uint8_t wall[16][16] = {};

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

    void print_wall_with_uint8_t(uint8_t (&n)[16][16]);
    void print_wall_with_arrow(uint8_t (&n)[16][16], uint8_t (&current)[2]);
    void print_cost();
    void print_route(uint8_t x, uint8_t y);

};

#endif