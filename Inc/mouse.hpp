#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "stdintdef.hpp"
#include "direction.hpp"

class Mouse{
    public:
    uint8_t x;
    uint8_t y;

    uint8_t direction;

    Mouse();

    void move_forward();
    void turn_90();
    void turn_inv90();
    void turn_180();
};

#endif