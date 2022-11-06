#ifndef PRINT_HPP_
#define PRINT_HPP_

#include <cstdint>
#include <vector>
#include "maze.hpp"

class Print{
    public:
    Maze *maze;

    Print(Maze *new_maze);

    void print_wall_with_uint8_t(uint8_t (&n)[16][16]);
    void print_wall_with_arrow(uint8_t (&n)[16][16], uint8_t (&current)[2], std::vector<std::vector<uint8_t>> question);
    void print_cost();
    void print_route(uint8_t x, uint8_t y, std::vector<std::vector<uint8_t>> question);
};

#endif