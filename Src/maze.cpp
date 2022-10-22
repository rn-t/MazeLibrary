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
        wall[i][0] = wall[i][0] | 0b1000;
        // 上側に壁を追加
        wall[i][15] = wall[i][15] | 0b0001;
        
        // 左側に壁を追加
        wall[0][i] = wall[0][i] | 0b0100;
        // 右側に壁を追加
        wall[15][i] = wall[15][i] | 0b0010;
    }

    //ゴール座標をもとに初期歩数を生成
}

void Maze::print_wall_with_uint8_t(uint8_t (&n)[16][16] ){
    for(int i = 0; i < 16; i++){
        if(i == 0) printf("┏");

        if((wall[i][15] & 0b1) == 0b1){
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
            if((wall[i][j] & 0b100) == 0b100){
                printf("┃");   
            }else{
                printf(" ");   
            }
            printf(" %.3d ", n[i][j]);
                
        }
        if((wall[15][j] & 0b10) == 0b10){
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
            if((wall[i][j] & 0b1000) == 0b1000){
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

        if((wall[i][15] & 0b1) == 0b1){
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
            if((wall[i][j] & 0b100) == 0b100){
                printf("┃");   
            }else{
                printf(" ");   
            }

            std::string s;
            switch (n[i][j])
            {
            case 0b1000:
                s = "👇";
                break;
            case 0b0100:
                s = "👈";
                break;
            case 0b0010:
                s = "👉";
                break;
            case 0b0001:
                s = "👆";
                break;
            default:
                s = "  ";
                break;
            }
            printf(" %s ", s.c_str());
                
        }
        if((wall[15][j] & 0b10) == 0b10){
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
            if((wall[i][j] & 0b1000) == 0b1000){
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

