#include <cstdint>

class Direction{
    public:
    static const uint8_t down = 0b1000;
    static const uint8_t left = 0b0100; 
    static const uint8_t right = 0b0010;
    static const uint8_t up = 0b0001;
};