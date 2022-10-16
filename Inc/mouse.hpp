#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include <cstdint>

class Mouse{
    public:
    uint8_t x;
    uint8_t y;
    char muki;

    Mouse(){
        x = 0;
        y = 0;
        //wasd操作っぽく管理する
        //wasd = ↑←↓→
        muki = 'w';
    };

};

#endif