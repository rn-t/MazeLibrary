#include <stdio.h>
#include <string>

#include "maze.hpp"
#include "direction.hpp"

/**
 * コンストラクタ 
*/
Maze::Maze(){
    //自明な壁(外枠)を生成
    for(uint8_t i = 0; i < 16; i++){
        // 下側に壁を追加
        wall[i][0] = wall[i][0] | Direction::down;
        // 上側に壁を追加
        wall[i][15] = wall[i][15] | Direction::up;
        
        // 左側に壁を追加
        wall[0][i] = wall[0][i] | Direction::left;
        // 右側に壁を追加
        wall[15][i] = wall[15][i] | Direction::right;
    }

    //ゴール座標をもとに初期歩数を生成
}

/**
 * @param w: 壁情報
*/
void Maze::wall_update(uint8_t x, uint8_t y, uint8_t w){
    wall[x][y] = w;

    if(x != 0 && (wall[x][y] & Direction::left) == Direction::left){
        wall[x - 1][y] = wall[x - 1][y] | Direction::right;
    }
    if(x != 15 && (wall[x][y] & Direction::right) == Direction::right){
        wall[x + 1][y] = wall[x + 1][y] | Direction::left;
    }
    if(y != 0 && (wall[x][y] & Direction::down) == Direction::down){
        wall[x][y - 1] = wall[x][y - 1] | Direction::up;
    }
    if(y != 15 && (wall[x][y] & Direction::up) == Direction::up){
        wall[x][y + 1] = wall[x][y + 1] | Direction::down;
    } 
}

void Maze::print_wall_with_uint8_t(uint8_t (&n)[16][16] ){
    for(int i = 0; i < 16; i++){
        if(i == 0) printf("┏");

        if((wall[i][15] & Direction::up) == Direction::up){
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
    for(int j = 15; j >= 0; j--){

        //横壁部分を描画
        for(int i = 0; i < 16; i++){
            if((wall[i][j] & Direction::left) == Direction::left){
                printf("┃");   
            }else{
                printf(" ");   
            }
            printf(" %.3d ", n[i][j]);
                
        }
        if((wall[15][j] & Direction::right) == Direction::right){
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
        for(int i = 0; i < 16; i++){
            if((wall[i][j] & Direction::down) == Direction::down){
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
void Maze::print_wall_with_arrow(uint8_t (&n)[16][16], uint8_t (&current)[2]){
    for(int i = 0; i < 16; i++){
        if(i == 0) printf("┏");

        if((wall[i][15] & Direction::up) == Direction::up){
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
    for(int j = 15; j >= 0; j--){

        //横壁部分を描画
        for(int i = 0; i < 16; i++){
            if((wall[i][j] & Direction::left) == Direction::left){
                printf("┃");   
            }else{
                printf(" ");   
            }

            std::string s;
            if(i == current[0] && j == current[1]){
                s = "🖱️";
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
        if((wall[15][j] & Direction::right) == Direction::right){
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
        for(int i = 0; i < 16; i++){
            if((wall[i][j] & Direction::down) == Direction::down){
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

void Maze::print_cost(){
    print_wall_with_uint8_t(cost);
}

/**
 * @param x 現在のx
 * @param y 現在のy
*/
void Maze::print_route(uint8_t x, uint8_t y){
    uint8_t current[2] = {x, y};
    print_wall_with_arrow(route, current);
}

