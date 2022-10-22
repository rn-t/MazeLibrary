#include "method.hpp"
#include "stdio.h"


AdachiMethod::AdachiMethod(Maze *new_maze, Mouse *new_mouse){
    this->maze = new_maze;
    this->mouse = new_mouse;

    for (uint8_t i = 0; i < 16; i++){
        for (uint8_t j = 0; j < 16; j++){
            maze->cost[i][j] = 255;
        }
    }

    //goalsにゴール座標を入れる
    std::vector<uint8_t> temp{maze->goal[0], maze->goal[1]};
    goals.push_back(temp);
    temp[0]++;
    goals.push_back(temp);
    temp[1]++;
    goals.push_back(temp);
    temp[0]--;
    goals.push_back(temp);

    //範囲for文というやつらしい
    for(const auto& g : goals){
        maze->cost[g[0]][g[1]] = 0;
        

    }

}

void AdachiMethod::cost_update(){
    uint8_t node_cost = 0;
    search_next = goals;
    //コスト0の地点(ゴール)から順に歩数マップを作成する。
    //スタート地点に来たら止める
    //マップのの全探索をしているので、あまり良くない。
    while (node_cost < 255){
        search_now = std::move(search_next);
        search_next.clear();

        for (const auto& s : search_now){
            uint8_t i = s[0];
            uint8_t j = s[1];

            //←の場合
            if(i != 0 && (maze->wall[i][j] & 0b0100) != 0b0100){
                if(maze->cost[i - 1][j] > (node_cost + 1)){
                    maze->cost[i - 1][j] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i - 1][j] = maze->route[i - 1][j] | 0b0010;
                    std::vector<uint8_t> temp{static_cast<uint8_t>(i - 1), j};
                    search_next.push_back(temp);
                }
            }
            //→の場合
            if(i != 15 && (maze->wall[i][j] & 0b0010) != 0b0010){
                if(maze->cost[i + 1][j] > (node_cost + 1)){
                    maze->cost[i + 1][j] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i + 1][j] = maze->route[i + 1][j] | 0b0100;
                    std::vector<uint8_t> temp{static_cast<uint8_t>(i + 1), j};
                    search_next.push_back(temp);
                }
            }
            //↓の場合
            if(j != 0 && (maze->wall[i][j] & 0b1000) != 0b1000){
                if(maze->cost[i][j - 1] > (node_cost + 1)){
                    maze->cost[i][j - 1] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i][j - 1] = maze->route[i][j - 1] | 0b0001;
                    std::vector<uint8_t> temp{i, static_cast<uint8_t>(j - 1)};
                    search_next.push_back(temp);
                }
            }
            //↑の場合
            if(j != 15 && (maze->wall[i][j] & 0b0001) != 0b0001){
                if(maze->cost[i][j + 1] > (node_cost + 1)){
                    maze->cost[i][j + 1] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i][j + 1] = maze->route[i][j + 1] | 0b1000;
                    std::vector<uint8_t> temp{i, static_cast<uint8_t>(j + 1)};
                    search_next.push_back(temp);
                }
            }

        }
                    
        if(maze->cost[mouse->x][mouse->y] < 255) break;

        node_cost++;
    }
}

//スタートからゴールまでの経路を計算し保存。その後に求めた経路以外を全部消してから戻す。
void AdachiMethod::delete_bad_route(){
    //通ったマス目を保存しておく
    std::vector< std::vector<uint8_t>> in_route;
    //routeの情報を保存しておく
    std::vector<uint8_t> route_buffer;
    std::vector<uint8_t> agent{0, 0};

    while(maze->cost[agent[0]][agent[1]] > 0){
        in_route.push_back(agent);
        route_buffer.push_back(maze->route[agent[0]][agent[1]]);
        
        switch(maze->route[agent[0]][agent[1]]){
            case 0b1000:
                agent[1]--;
                break;
            case 0b0100:
                agent[0]--;
                break;
            case 0b0010:
                agent[0]++;
                break;
            case 0b0001:
                agent[1]++;
                break;
        }
    }

    //経路情報を初期化
    for (uint8_t i = 0; i < 16; i++){
        for (uint8_t j = 0; j < 16; j++){
            maze->route[i][j] = 0;
        }
    }

    //バッファしておいた経路情報を書き込み
    for (uint8_t i = 0; i < route_buffer.size(); i++){
        maze->route[in_route[i][0]][in_route[i][1]] = route_buffer[i];
    }
    
}