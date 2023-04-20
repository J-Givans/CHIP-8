#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <array>
#include <cstdint>
#include <random>

namespace chip8
{
    inline std::random_device rd;
    inline std::mt19937 generator(rd());
    inline std::uniform_int_distribution<std::uint8_t> distribution(0, 255);

    class Registers
    {
    public:
        std::array<std::uint8_t, 16> registers = {0};
        std::uint16_t pc;
        std::uint16_t indexRegister {};
    };
}

#endif