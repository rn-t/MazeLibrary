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
        muki = 'u';
    };

};

#endif