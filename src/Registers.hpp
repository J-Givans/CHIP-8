#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <array>
#include <cstdint>

namespace chip8
{
    class Registers
    {
    public:
        std::array<std::uint8_t, 16> registers = {0};
    };
}

#endif