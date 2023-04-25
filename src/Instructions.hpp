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

    /// \brief ADD Vx, byte
    /// \brief Set Vx = Vk + kk
    void op7xkk(Registers& reg) noexcept;

    /// \brief LD Vx, Vy
    /// \brief Set Vx = Vy
    void op8xy0(Registers& reg) noexcept;

    /// \brief OR Vx, Vy
    /// \brief Set Vx = Vx or Vy
    void op8xy1(Registers& reg) noexcept;

    /// \brief AND Vx, Vy
    /// \brief Set Vx = Vx AND Vy
    void op8xy2(Registers& reg) noexcept;

    /// \brief XOR Vx, Vy
    /// \brief Set Vx = Vx XOR Vy
    void op8xy3(Registers& reg) noexcept;

    /// \brief ADD Vx, Vy
    /// \brief Set Vx = Vx + Vy and set VF = carry
    /// \details Sum Vx and Vy. If the result is greater than 8 bits, set VF to 1, otherwise 0.
    /// \details Keep only the lowest 8 bits of the result and store them in Vx
    void op8xy4(Registers& reg) noexcept;

    /// \brief SUB Vx, Vy
    /// \brief Set Vx = Vx - Vy and set VF = NOT borrow
    /// \details If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx
    void op8xy5(Registers& reg) noexcept;

    /// \brief SHR Vx
    /// \brief Set Vx Vx SHR 1
    /// \details If the least significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2
    void op8xy6(Registers& reg) noexcept;

    /// \brief SUBN Vx, Vy
    /// \brief Set Vx = Vy - Vx, and set VF = NOT borrow
    /// \details If Vy > Vx, set VF = 1, otherwise 0. Then subtract Vx from Vy, and store the results in Vx
    void op8xy7(Registers& reg) noexcept;

    /// \brief SHL Vx { , Vy }
    /// \brief Set Vx = Vx SHL 1
    /// \details If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2
    void op8xyE(Registers& reg) noexcept;

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