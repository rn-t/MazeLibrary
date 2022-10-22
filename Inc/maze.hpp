#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <cstdint>


class Maze{
    public:
    
    class Direction{
        public:
        static const uint8_t down = 0b1000;
        static const uint8_t left = 0b0100; 
        static const uint8_t right = 0b0010;
        static const uint8_t up = 0b0001;
    };
    
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
    uint8_t cost[16][16];

    /**
     * @brief 進める向き。二進数で↓←→↑
     * 
     */
    uint8_t route[16][16] = {};

    Maze();

    void print_wall_with_uint8_t(uint8_t (&n)[16][16]);
    void print_wall_with_arrow(uint8_t (&n)[16][16] );
    void print_cost();
    void print_route();

};

#endif