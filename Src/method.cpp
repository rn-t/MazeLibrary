#include "method.hpp"

AdachiMethod::AdachiMethod(Maze *new_maze, Mouse *new_mouse){
    this->maze = new_maze;
    this->mouse = new_mouse;

    set_goals(maze->goal);
    cost_reset();

}

void AdachiMethod::set_start(std::vector<uint8_t> s){
    start = s;
}

void AdachiMethod::set_goals(std::vector< std::vector<uint8_t>> g){
    goals = g;
}

void AdachiMethod::cost_reset(){
    for (uint8_t i = 0; i < 16; i++){
        for (uint8_t j = 0; j < 16; j++){
            maze->cost[i][j] = 255;
        }
    }
    
    //範囲for文というやつらしい
    for(const auto& g : goals){
        maze->cost[g[0]][g[1]] = 0;
    }
}

void AdachiMethod::route_reset(){
    for (uint8_t i = 0; i < 16; i++){
        for (uint8_t j = 0; j < 16; j++){
            maze->route[i][j] = 0;
        }
    }
}

void AdachiMethod::set_wall_at_unknown(){
    const uint8_t full_wall = Direction::up + Direction::down + Direction::left + Direction::right;
    for (uint8_t i = 0; i < 16; i++){
        for (uint8_t j = 0; j < 16; j++){
            if((maze->wall[i][j] & Maze::IS_SEARCHED) == 0){
                maze->wall_update(i, j, full_wall);
            }
        }
    }
}

void AdachiMethod::cost_refresh(){
    cost_reset();
    route_reset();
    uint8_t node_cost = 0;
    search_next = goals;
    //コスト0の地点(ゴール)から順に歩数マップを作成する。
    //マウスの現在地に来たら止める
    while (node_cost < 255){
        search_now = std::move(search_next);
        search_next.clear();

        for (const auto& s : search_now){
            uint8_t i = s[0];
            uint8_t j = s[1];

            //←の場合
            if(i != 0 && (maze->wall[i][j] & Direction::left) != Direction::left){
                if(maze->cost[i - 1][j] > (node_cost + 1)){
                    maze->cost[i - 1][j] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i - 1][j] = Direction::right;
                    std::vector<uint8_t> temp{static_cast<uint8_t>(i - 1), j};
                    search_next.push_back(temp);
                }
            }
            //→の場合
            if(i != 15 && (maze->wall[i][j] & Direction::right) != Direction::right){
                if(maze->cost[i + 1][j] > (node_cost + 1)){
                    maze->cost[i + 1][j] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i + 1][j] = Direction::left;
                    std::vector<uint8_t> temp{static_cast<uint8_t>(i + 1), j};
                    search_next.push_back(temp);
                }
            }
            //↓の場合
            if(j != 0 && (maze->wall[i][j] & Direction::down) != Direction::down){
                if(maze->cost[i][j - 1] > (node_cost + 1)){
                    maze->cost[i][j - 1] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i][j - 1] = Direction::up;
                    std::vector<uint8_t> temp{i, static_cast<uint8_t>(j - 1)};
                    search_next.push_back(temp);
                }
            }
            //↑の場合
            if(j != 15 && (maze->wall[i][j] & Direction::up) != Direction::up){
                if(maze->cost[i][j + 1] > (node_cost + 1)){
                    maze->cost[i][j + 1] = node_cost + 1;
                    //このノードに向けた矢印を追加する
                    maze->route[i][j + 1] = Direction::down;
                    std::vector<uint8_t> temp{i, static_cast<uint8_t>(j + 1)};
                    search_next.push_back(temp);
                }
            }

        }
                    
        if(maze->cost[start[0]][start[1]] < 255) break;

        node_cost++;
    }
}

//スタートからゴールまでの経路を計算し保存。その後に求めた経路以外を全部消してから戻す。
void AdachiMethod::delete_bad_route(){
    //通ったマス目を保存しておく
    std::vector< std::vector<uint8_t>> in_route;
    //routeの情報を保存しておく
    std::vector<uint8_t> route_buffer;
    std::vector<uint8_t> agent{start[0], start[1]};

    while(maze->cost[agent[0]][agent[1]] > 0){
        in_route.push_back(agent);
        route_buffer.push_back(maze->route[agent[0]][agent[1]]);
        
        switch(maze->route[agent[0]][agent[1]]){
            case Direction::down:
                agent[1]--;
                break;
            case Direction::left:
                agent[0]--;
                break;
            case Direction::right:
                agent[0]++;
                break;
            case Direction::up:
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

/**
 * ゴールに入ってたら1、そうでなければ0
*/
uint8_t AdachiMethod::goal_check(){
    std::vector<uint8_t> current{mouse->x, mouse->y};
    
    auto res = std::find(goals.begin(), goals.end(), current);
    if(res == goals.end()){
        return 0;
    }else{
        return 1;
    }
}

std::vector< std::vector<uint8_t>> AdachiMethod::get_unknown_in_shortest(){
    
    std::vector<uint8_t> temp_start;
    std::vector< std::vector<uint8_t>> temp_goals;
    temp_start = start;
    temp_goals = goals;
    set_start(maze->start[0]);
    set_goals(maze->goal);
    cost_refresh();
    delete_bad_route();

    std::vector< std::vector<uint8_t>> out;

    for (uint8_t i = 0; i < 16; i++){
        for (uint8_t j = 0; j < 16; j++){
            if(maze->route[i][j] != 0 && ((maze->wall[i][j] & Maze::IS_SEARCHED) == 0)){
                std::vector<uint8_t> temp_vec{i, j};
                out.push_back(temp_vec);
            }
        }
    }
    set_start(temp_start);
    set_goals(temp_goals);
    return out;

}