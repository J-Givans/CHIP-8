#ifndef TIMERS_HPP
#define TIMERS_HPP

#include <cstdint>

namespace chip8
{
    struct Timers
    {
        uint8_t delayTimer {};
        uint8_t soundTimer {};
    };
}

#endif