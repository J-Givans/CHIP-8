#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include "Memory.hpp"
#include "Timers.hpp"

#include <array>
#include <cstdint>
#include <random>

#include <gsl/assert>

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

        /// \brief Get the current value of the index register
        /// \returns The value of the index register
        constexpr std::uint16_t getIndexRegister() const noexcept;

        /// \brief Get the current value of the program counter
        /// \returns The value of the program counter
        constexpr std::uint16_t getProgramCounter() const noexcept;

        /// \brief Get the value of the 8-bit register at the given index (read and write access)
        /// \param[in] index The index of the 8-bit register
        /// \returns The value of the 8-bit register
        constexpr uint8_t& operator[](uint8_t index) noexcept;

        /// \brief Get the value of the 8-bit register at the given index (read-only access)
        /// \param[in] index The index of the 8-bit register
        /// \returns The value of the 8-bit register
        constexpr uint8_t const& operator[](uint8_t index) const noexcept;

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

        /// \brief ADD Vx, Vy
        /// \brief Set Vx = Vx + Vy and set VF = carry
        /// \details Sum Vx and Vy. If the result is greater than 8 bits, set VF to 1, otherwise 0.
        /// \details Keep only the lowest 8 bits of the result and store them in Vx
        void op8xy4() noexcept;

        /// \brief SUB Vx, Vy
        /// \brief Set Vx = Vx - Vy and set VF = NOT borrow
        /// \details If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx
        void op8xy5() noexcept;

        /// \brief SHR Vx
        /// \brief Set Vx Vx SHR 1
        /// \details If the least significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2
        void op8xy6() noexcept;

        /// \brief SUBN Vx, Vy
        /// \brief Set Vx = Vy - Vx, and set VF = NOT borrow
        /// \details If Vy > Vx, set VF = 1, otherwise 0. Then subtract Vx from Vy, and store the results in Vx
        void op8xy7() noexcept;

        /// \brief SHL Vx { , Vy }
        /// \brief Set Vx = Vx SHL 1
        /// \details If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2
        void op8xyE() noexcept;

        /// \brief SNE Vx, Vy
        /// \brief Skip next instruction if Vx != Vy
        void op9xy0() noexcept;

        /// \brief LD I, addr
        /// \brief Set I = nnn
        void opAnnn() noexcept;

        /// \brief JP V0, addr
        /// \brief Jump to location nnn + V0
        void opBnnn() noexcept;

        /// \brief RND Vx, byte
        /// \brief Set Vx = random byte AND kk
        void opCxkk() noexcept;

        /// \brief SKP Vx
        /// \brief Skip the next instruction if the key with the value of Vx is pressed
        void opEx9E() noexcept;

        /// \brief SKNP Vx
        /// \brief Skip the next instruction if the key with the value of Vx is not pressed
        void opExA1() noexcept;

        /// \brief LD Vx, DT
        /// \brief Set Vx = delay timer value
        void opFx07(Timers const& timers) noexcept;

        /// \brief LD Vx, K
        /// \brief Wait for a key press, and then store the value of the key pressed in Vx
        void opFx0A() noexcept;

        /// \brief ADD I, Vx
        /// \brief Set I = I + Vx
        void opFx1E() noexcept;

        /// \brief LD F, Vx
        /// \brief Set I = location of sprite for digit Vx
        void opFx29() noexcept;
    };

    constexpr std::uint16_t Registers::getIndexRegister() const noexcept
    {
        return idxRegister;
    }

    constexpr std::uint16_t Registers::getProgramCounter() const noexcept
    {
        return pc;
    }

    constexpr uint8_t& Registers::operator[](uint8_t index) noexcept
    {
        Expects(index >= 0 and index <= 15);
        return byteRegisters[index];
    }

    constexpr uint8_t const& Registers::operator[](uint8_t index) const noexcept
    {
        Expects(index >= 0 and index <= 15);
        return byteRegisters[index];
    }
}

#endif