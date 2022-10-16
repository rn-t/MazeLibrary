#ifndef METHOD_HPP_
#define METHOD_HPP_

#include <cstdint>

#include "maze.hpp"
#include "mouse.hpp"


class AdachiMethod{
    public:
    Maze *maze;
    Mouse *mouse;

    AdachiMethod(Maze *new_maze, Mouse *new_mouse);
    void cost_update();
};



#endif