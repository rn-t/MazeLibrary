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
    //2015 学生大会 クラシック競技
    uint8_t map[16][16]={{14,6,4,6,7,14,6,4,4,5,12,4,5,12,7,15},{12,6,2,6,4,4,4,3,11,10,1,11,10,2,4,5},{8,7,15,14,1,11,10,5,15,14,2,5,15,14,1,9},{10,4,5,12,3,15,14,1,13,12,4,1,13,12,3,11},{12,3,10,2,5,13,14,2,2,3,11,10,3,8,7,15},{8,7,15,12,2,3,12,4,4,5,12,4,5,10,5,13},{10,5,12,1,13,12,3,11,9,10,1,11,10,5,10,1},{13,10,3,10,1,8,7,12,1,14,1,15,14,1,12,3},{8,7,15,14,1,8,7,10,3,14,1,13,12,1,8,7},{8,5,13,12,1,10,5,13,13,12,2,2,1,11,10,5},{9,10,2,1,11,12,2,2,2,1,15,12,3,15,14,1},{9,15,14,3,15,10,4,5,14,1,13,8,4,5,12,3},{8,6,4,6,4,7,11,10,4,2,2,1,11,10,1,15},{9,14,1,13,8,7,15,12,3,15,12,3,15,14,1,13},{9,14,1,8,2,5,13,8,5,13,8,5,13,12,2,3},{10,6,2,3,14,2,2,3,10,2,3,10,2,2,7,15}};	
    
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
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
       
    return 0;
}