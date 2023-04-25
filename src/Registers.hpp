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

        /// \brief Skip next instruction if Vx = kk
        void op3xkk() noexcept;
        
        /// \brief SNE Vx, byte
        /// \brief Skip next instruction if Vx != kk
        void op4xkk() noexcept;

        /// \brief SE Vx, Vy
        /// \brief Skip next instruction if Vx = Vy
        void op5xy0() noexcept;

        /// \brief LD Vx, byte
        /// \brief Set Vx = kk
        void op6xkk() noexcept;

        /// \brief ADD Vx, byte
        /// \brief Set Vx = Vk + kk
        void op7xkk() noexcept;

        /// \brief LD Vx, Vy
        /// \brief Set Vx = Vy
        void op8xy0() noexcept;

        /// \brief OR Vx, Vy
        /// \brief Set Vx = Vx or Vy
        void op8xy1() noexcept;

        /// \brief AND Vx, Vy
        /// \brief Set Vx = Vx AND Vy
        void op8xy2() noexcept;

        /// \brief XOR Vx, Vy
        /// \brief Set Vx = Vx XOR Vy
        void op8xy3() noexcept;
    };
}

#endif