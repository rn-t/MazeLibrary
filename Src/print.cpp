#include "direction.hpp"
#include "print.hpp"
#include <string>
#include <algorithm>

void Print::print_wall_with_uint8_t(uint8_t (&n)[16][16] ){
    for(int8_t i = 0; i < 16; i++){
        if(i == 0) printf("┏");

        if((maze->wall[i][15] & Direction::up) == Direction::up){
            printf("━━━━━");
        }else{
            printf("     ");
        }
        if(i < 15){
            printf("┳");
        }else if(i == 15){
            printf("┓\n");
        }
    }
    for(uint8_t j0 = 0; j0 < 16; j0++){
        uint8_t j = 15 - j0;
        //横壁部分を描画
        for(int8_t i = 0; i < 16; i++){
            if((maze->wall[i][j] & Direction::left) == Direction::left){
                printf("┃");   
            }else{
                printf(" ");   
            }
            printf(" %.3d ", n[i][j]);
                
        }
        if((maze->wall[15][j] & Direction::right) == Direction::right){
            printf("┃");   
        }else{
            printf(" ");   
        }
        printf("\n");

        //下壁部分を描画
        if(j > 0){
            printf("┣");   
        }else if(j == 0){
            printf("┗");   
        }
        for(uint8_t i = 0; i < 16; i++){
            if((maze->wall[i][j] & Direction::down) == Direction::down){
                printf("━━━━━");
            }else{
                printf("     ");
            }
            if(i < 15){
                if(j > 0){
                    printf("╋");
                }else if(j == 0){
                    printf("┻");
                }
            }else if(i == 15){
                if(j > 0){
                    printf("┫\n");
                }else if(j == 0){
                    printf("┛\n");
                }
                
            }
        }
    }
}

/**
 * @brief 方向と現在地をいい感じに表示する
 * @param n: 方向を保存した2次元配列
 * @param current: 現在地を保存した配列{x, y} 
*/
void Print::print_wall_with_arrow(uint8_t (&n)[16][16], uint8_t (&current)[2], std::vector<std::vector<uint8_t>> question){
    for(uint8_t i = 0; i < 16; i++){
        if(i == 0) printf("┏");

        if((maze->wall[i][15] & Direction::up) == Direction::up){
            printf("━━━━");
        }else{
            printf("    ");
        }
        if(i < 15){
            printf("┳");
        }else if(i == 15){
            printf("┓\n");
        }
    }
    for(uint8_t j0 = 0; j0 < 16; j0++){
        uint8_t j = 15 - j0;

        //横壁部分を描画
        for(uint8_t i = 0; i < 16; i++){
            if((maze->wall[i][j] & Direction::left) == Direction::left){
                printf("┃");   
            }else{
                printf(" ");   
            }

            std::string s;
            std::vector<uint8_t> vec{i, j};
            if(i == current[0] && j == current[1]){
                s = "🖱️";
            }else if(maze->start.end() != std::find(maze->start.begin(), maze->start.end(), vec)){
                s = "🌟";
            }
            else if(maze->goal.end() != std::find(maze->goal.begin(), maze->goal.end(), vec)){
                s = "🏁";
            }else if(question.end() != std::find(question.begin(), question.end(), vec)){
                s = "❓";
            }else{
                switch (n[i][j]){
                case Direction::down:
                    s = "👇";
                    break;
                case Direction::left:
                    s = "👈";
                    break;
                case Direction::right:
                    s = "👉";
                    break;
                case Direction::up:
                    s = "👆";
                    break;
                default:
                    s = "  ";
                    break;
                }
            }
            
            printf(" %s ", s.c_str());
                
        }
        if((maze->wall[15][j] & Direction::right) == Direction::right){
            printf("┃");   
        }else{
            printf(" ");   
        }
        printf("\n");

        //下壁部分を描画
        if(j > 0){
            printf("┣");   
        }else if(j == 0){
            printf("┗");   
        }
        for(uint8_t i = 0; i < 16; i++){
            if((maze->wall[i][j] & Direction::down) == Direction::down){
                printf("━━━━");
            }else{
                printf("    ");
            }
            if(i < 15){
                if(j > 0){
                    printf("╋");
                }else if(j == 0){
                    printf("┻");
                }
            }else if(i == 15){
                if(j > 0){
                    printf("┫\n");
                }else if(j == 0){
                    printf("┛\n");
                }
                
            }
        }
    }
}

void Print::print_cost(){
    print_wall_with_uint8_t(maze->cost);
}

/**
 * @param x 現在のx
 * @param y 現在のy
*/
void Print::print_route(uint8_t x, uint8_t y, std::vector<std::vector<uint8_t>> question){
    uint8_t current[2] = {x, y};
    print_wall_with_arrow(maze->route, current, question);
}