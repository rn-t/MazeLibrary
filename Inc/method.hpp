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

    std::vector<uint8_t> start;
    std::vector< std::vector<uint8_t>> goals;
    
    std::vector< std::vector<uint8_t>> search_now;
    std::vector< std::vector<uint8_t>> search_next;

    AdachiMethod(Maze *new_maze, Mouse *new_mouse);

    void set_start(std::vector<uint8_t> s);
    void set_goals(std::vector< std::vector<uint8_t>> g);

    void cost_reset();
    void route_reset();

    void cost_refresh();
    void delete_bad_route();
    uint8_t goal_check();

    //todo ゴール座標を最短経路のうち未探索の場所に設定するプログラムを作成
    std::vector< std::vector<uint8_t>> get_unknown_in_shortest();
};

#endif