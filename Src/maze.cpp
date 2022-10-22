#include <stdio.h>
#include <string>

#include "maze.hpp"

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

void Maze::print_wall_with_arrow(uint8_t (&n)[16][16] ){
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
            switch (n[i][j])
            {
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

void Maze::print_route(){
    print_wall_with_arrow(route);
}

