#include <stdio.h>

#include "maze.hpp"

void Maze::print(){
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
            printf(" %.2d ", 0);
                
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