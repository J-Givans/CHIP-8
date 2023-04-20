#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include "Registers.hpp"
#include "Stack.hpp"
#include "Video.hpp"

namespace chip8
{
    inline std::uint16_t opcode {};

    /// \brief Clear the video buffer
    constexpr void op00E0(Video& video) noexcept;

    /// \brief Return from a subroutine
    /// \param[in] stack A reference to the stack containing instructions to execute
    /// \param[in] reg A reference to the register containing the program counter
    void op00EE(Stack& stack, Registers& reg) noexcept;

    /// \brief Jump to location nnn
    /// \details The interpreter sets the program counter to nnn
    void op1nnn(Registers& reg) noexcept;

    /// \brief Call subroutine at nnn
    void op2nnn(Stack& stack, Registers& reg);

    /// \brief Skip next instruction if Vx = kk
    void op3xkk(Registers& reg);

    /// \brief SNE Vx, byte
    /// \brief Skip next instruction if Vx != kk
    void op4xkk(Registers& reg);

    /// \brief SE Vx, Vy
    /// \brief Skip next instruction if Vx = Vy
    void op5xy0(Registers& reg);

    /// \brief LD Vx, byte
    /// \brief Set Vx = kk
    void op6xkk(Registers& reg);

    /// \brief ADD Vx, byte
    /// \brief Set Vx = Vk + kk
    void op7xkk(Registers& reg);

    /// \brief LD Vx, Vy
    /// \brief Set Vx = Vy
    void op8xy0(Registers& reg);

    /// \brief OR Vx, Vy
    /// \brief Set Vx = Vx or Vy
    void op8xy1(Registers& reg);
}

#endif