#ifndef METHOD_HPP_
#define METHOD_HPP_

#include <cstdint>
#include <vector>

#include "maze.hpp"
#include "mouse.hpp"


class AdachiMethod{
    public:
    Maze *maze;
    Mouse *mouse;

    std::vector< std::vector<uint8_t>> goals;
    
    std::vector< std::vector<uint8_t>> search_now;
    std::vector< std::vector<uint8_t>> search_next;

    /**
     * @brief 二進数で↓←→↑
     * 
     */
    uint8_t route[16][16] = {};

    AdachiMethod(Maze *new_maze, Mouse *new_mouse);
    void cost_update();
};



#endif