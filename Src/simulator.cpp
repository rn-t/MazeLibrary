#include <stdio.h>
#include <cstdint>
#include <chrono>
#include <thread>

#include "maze.hpp"
#include "method.hpp"
#include "direction.hpp"

int16_t direction_to_deg(uint8_t direction){
    uint16_t out = 0;
    switch(direction){
            case Direction::up:
                out = 0;
                break;
            case Direction::down:
                out = 180;
                break;
            case Direction::left:
                out = 90;
                break;
            case Direction::right:
                out = -90;
                break;
        }
    return out;
}

int16_t deg_sub(int16_t a, int16_t b){
    int16_t out = a - b;
    while(out <= -180 || 180 < out){
        if(out <= -180){
            out += 360;
        }else if(180 < out){
            out -= 360;
        }
    }
    return out;
}

int main(void){
    Maze maze;
    Maze true_maze;
    Mouse mouse;

    //迷路データはhttp://mice.deca.jp/maze/ より
    //2018の全日本クラシックらしい
    uint8_t map[16][16]={{14,6,5,12,4,4,6,6,6,6,4,4,5,12,6,7},{14,6,0,3,9,9,12,6,4,5,9,9,10,0,6,7},{14,4,2,6,3,9,8,5,9,9,9,10,6,2,4,7},{12,2,6,6,6,3,9,9,9,9,10,6,6,6,2,5},{9,12,6,6,6,6,3,9,9,10,6,6,6,6,5,9},{9,9,12,6,6,6,6,3,10,4,6,4,5,13,9,9},{9,9,9,12,5,12,4,7,14,0,5,9,9,9,9,9},{9,9,9,9,9,9,9,12,5,11,8,1,9,9,9,9},{9,9,9,9,9,9,9,10,2,5,11,8,0,3,9,9},{9,9,9,9,9,9,10,4,4,3,14,3,10,5,9,9},{9,9,9,9,9,9,12,1,9,12,5,12,5,9,9,9},{9,9,9,9,9,10,1,9,9,9,9,9,9,9,9,9},{9,9,9,9,9,12,0,1,9,9,9,9,9,9,9,9},{9,9,9,9,9,9,9,9,10,3,10,3,9,9,9,9},{9,9,10,3,8,2,2,1,14,6,6,6,2,3,9,9},{10,3,14,6,2,6,6,3,14,6,6,6,6,6,2,3}};
    
    for(uint8_t i = 0; i < 16; i++){
        for(uint8_t j = 0; j < 16; j++){
            true_maze.wall[i][j] = map[i][j];
        }
    }

    AdachiMethod method(&maze, &mouse);

    for(uint8_t step = 0; step < 3; step++){
        if(step == 0 || step == 2){
            method.set_goals(maze.goal);
        }else{
            method.set_goals(maze.start);
        }

        while(1){

            //真の迷路からの壁情報の読み込み
            maze.wall_update(mouse.x, mouse.y, true_maze.wall[mouse.x][mouse.y]);
            
            //コストの再計算
            method.cost_refresh();
            //いらない経路の削除
            method.delete_bad_route();
            
            printf("\033[0;0H");
            maze.print_route(mouse.x, mouse.y);
            //maze.print_cost();

            if(method.goal_check() || step == 2) break;
            int16_t mouse_deg = direction_to_deg(mouse.direction);
            int16_t maze_deg = direction_to_deg(maze.route[mouse.x][mouse.y]);

            int16_t turn_deg = deg_sub(mouse_deg, maze_deg);

            switch(turn_deg){
                case 90:
                    mouse.turn_inv90();
                    break;
                case -90:
                    mouse.turn_90();
                    break;
                case 180:
                    mouse.turn_180();
                    break;
            }
            mouse.move_forward();

            //500ms待つ
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
       
    return 0;
}