#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include "Memory.hpp"

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
        std::array<std::uint8_t, 16> byteRegisters = {0};
        std::uint16_t pc = StartAddress;
        std::uint16_t idxRegister {};

        /// \brief Default constructor
        constexpr Registers() noexcept = default;

        /// \brief Jump to location nnn
        /// \details The interpreter sets the program counter to nnn
        void op1nnn() noexcept;
    };
}

#endif