#include <stdio.h>
#include <cstdint>
#include <chrono>
#include <thread>

#include "maze.hpp"
#include "method.hpp"

int main(void){
    Maze maze;
    Maze true_maze;
    Mouse mouse;

    //迷路データはhttp://mice.deca.jp/maze/ より
    //2018の全日本クラシックらしい
    uint8_t map[16][16]={{14,6,5,12,4,4,6,6,6,6,4,4,5,12,6,7},{14,6,0,3,9,9,12,6,4,5,9,9,10,0,6,7},{14,4,2,6,3,9,8,5,9,9,9,10,6,2,4,7},{12,2,6,6,6,3,9,9,9,9,10,6,6,6,2,5},{9,12,6,6,6,6,3,9,9,10,6,6,6,6,5,9},{9,9,12,6,6,6,6,3,10,4,6,4,5,13,9,9},{9,9,9,12,5,12,4,7,14,0,5,9,9,9,9,9},{9,9,9,9,9,9,9,12,5,11,8,1,9,9,9,9},{9,9,9,9,9,9,9,10,2,5,11,8,0,3,9,9},{9,9,9,9,9,9,10,4,4,3,14,3,10,5,9,9},{9,9,9,9,9,9,12,1,9,12,5,12,5,9,9,9},{9,9,9,9,9,10,1,9,9,9,9,9,9,9,9,9},{9,9,9,9,9,12,0,1,9,9,9,9,9,9,9,9},{9,9,9,9,9,9,9,9,10,3,10,3,9,9,9,9},{9,9,10,3,8,2,2,1,14,6,6,6,2,3,9,9},{10,3,14,6,2,6,6,3,14,6,6,6,6,6,2,3}};
    
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            true_maze.wall[i][j] = map[i][j];
        }
    }

    AdachiMethod method(&maze, &mouse);

    while(method.goal_check() == 0){

        //真の迷路からの壁情報の読み込み
        maze.wall[mouse.x][mouse.y] = true_maze.wall[mouse.x][mouse.y];


        method.cost_refresh();
        method.delete_bad_route();
        maze.print_route();        

        //500ms待つ
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
       
    return 0;
}