#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include "Registers.hpp"
#include "Stack.hpp"
#include "Video.hpp"

namespace chip8
{
    /// \brief Clear the video buffer
    constexpr void op00E0(Video& video) noexcept;

    /// \brief Return from a subroutine
    /// \param[in] stack A reference to the stack containing instructions to execute
    /// \param[in] reg A reference to the register containing the program counter
    void op00EE(Stack& stack, Registers& reg) noexcept;
}

#endif