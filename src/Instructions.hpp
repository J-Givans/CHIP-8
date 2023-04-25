#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include "Registers.hpp"
#include "Stack.hpp"
#include "Video.hpp"
#include "Memory.hpp"
#include "CPU.hpp"

namespace chip8
{
    inline std::uint16_t opcode {};

    /// \brief SNE Vx, Vy
    /// \brief Skip next instruction if Vx != Vy
    void op9xy0(Registers& reg) noexcept;

    /// \brief LD I, addr
    /// \brief Set I = nnn
    void opAnnn(Registers& reg) noexcept;

    /// \brief JP V0, addr
    /// \brief Jump to location nnn + V0
    void opBnnn(Registers& reg) noexcept;

    /// \brief RND Vx, byte
    /// \brief Set Vx = random byte AND kk
    void opCxkk(Registers& reg) noexcept;

    /// \brief SKP Vx
    /// \brief Skip the next instruction if the key with the value of Vx is pressed
    void opEx9E(Registers& reg) noexcept;

    /// \brief SKNP Vx
    /// \brief Skip the next instruction if the key with the value of Vx is not pressed
    void opExA1(Registers& reg) noexcept;

    /// \brief LD Vx, K
    /// \brief Wait for a key press, and then store the value of the key pressed in Vx
    void opFx0A(Registers& reg) noexcept;

    /// \brief ADD I, Vx
    /// \brief Set I = I + Vx
    void opFx1E(Registers& reg) noexcept;

    /// \brief LD F, Vx
    /// \brief Set I = location of sprite for digit Vx
    void opFx29(Registers& reg) noexcept;
}

#endif