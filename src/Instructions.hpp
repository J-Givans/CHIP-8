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

    /// \brief ADD I, Vx
    /// \brief Set I = I + Vx
    void opFx1E(Registers& reg) noexcept;

    /// \brief LD F, Vx
    /// \brief Set I = location of sprite for digit Vx
    void opFx29(Registers& reg) noexcept;
}

#endif