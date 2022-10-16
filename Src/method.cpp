#include "method.hpp"

AdachiMethod::AdachiMethod(Maze *new_maze, Mouse *new_mouse){
    this->maze = new_maze;
    this->mouse = new_mouse;

    for (uint8_t i = 0; i < 16; i++){
        for (uint8_t j = 0; j < 16; j++){
            maze->cost[i][j] = 255;
        }
    }

    

    maze->cost[maze->goal[0]][maze->goal[1]] = 0;
    maze->cost[maze->goal[0] + 1][maze->goal[1]] = 0;
    maze->cost[maze->goal[0]][maze->goal[1] + 1] = 0;
    maze->cost[maze->goal[0] + 1][maze->goal[1] + 1] = 0;

}

void AdachiMethod::cost_update(){
    uint8_t node_cost = 0;
    //コスト0の地点(ゴール)から順に歩数マップを作成する。
    //スタート地点に来たら止める
    //マップのの全探索をしているので、あまり良くない。
    while (node_cost < 255){
        for(uint8_t i = 0; i < 16; i++){
            for(uint8_t j = 0; j < 16; j++){
                if(maze->cost[i][j] == node_cost){
                    if(i != 0 && (maze->wall[i][j] & 0b0100) != 0b0100){
                        if(maze->cost[i - 1][j] > (node_cost + 1)) maze->cost[i - 1][j] = node_cost + 1;
                    }
                    if(i != 15 && (maze->wall[i][j] & 0b0010) != 0b0010){
                        if(maze->cost[i + 1][j] > (node_cost + 1)) maze->cost[i + 1][j] = node_cost + 1;
                    }
                    
                    if(j != 0 && (maze->wall[i][j] & 0b1000) != 0b1000){
                        if(maze->cost[i][j - 1] > (node_cost + 1)) maze->cost[i][j - 1] = node_cost + 1;
                    }
                    if(j != 15 && (maze->wall[i][j] & 0b0001) != 0b0001){
                        if(maze->cost[i][j + 1] > (node_cost + 1)) maze->cost[i][j + 1] = node_cost + 1;
                    }
                    
                    
                }
            }
        }
        if(maze->cost[mouse->x][mouse->y] < 255) break;

        node_cost++;
    }
}