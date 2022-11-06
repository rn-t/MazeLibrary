#include "mouse.hpp"


Mouse::Mouse(){
    x = 0;
    y = 0;
        
    direction = Direction::up;
}

void Mouse::move_forward(){ 
    switch (direction){
        case Direction::up:
            y++;
            break;
        case Direction::down:
            y--;
            break;
        case Direction::left:
            x--;
            break;
        case Direction::right:
            x++;
            break;
    }
}


void Mouse::turn_90(){
    switch (direction){
        case Direction::up:
            direction = Direction::left;
            break;
        case Direction::left:
            direction = Direction::down;
            break;
        case Direction::down:
            direction = Direction::right;
            break;
        case Direction::right:
            direction = Direction::up;
            break;
    }
}

void Mouse::turn_inv90(){
    switch (direction){
        case Direction::up:
            direction = Direction::right;
            break;
        case Direction::right:
            direction = Direction::down;
            break;
        case Direction::down:
            direction = Direction::left;
            break;
        case Direction::left:
            direction = Direction::up;
            break;
    }
}

void Mouse::turn_180(){
    switch (direction){
        case Direction::up:
            direction = Direction::down;
            break;
        case Direction::down:
            direction = Direction::up;
            break;
        case Direction::left:
            direction = Direction::right;
            break;
        case Direction::right:
            direction = Direction::left;
            break;
    }
}