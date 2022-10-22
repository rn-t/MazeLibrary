#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include <cstdint>

class Mouse{
    public:
    uint8_t x;
    uint8_t y;

    enum class Direction: uint8_t { up, down, left, right};

    Direction direction;

    Mouse();

    void move_forward();
    void turn_90();
    void turn_inv90();
    void turn_180();
};

#endif