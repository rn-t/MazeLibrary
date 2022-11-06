#include <stdio.h>

#include <algorithm>

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
    wall[x][y] = wall[x][y] | IS_SEARCHED;

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



