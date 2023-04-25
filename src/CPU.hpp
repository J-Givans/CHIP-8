#ifndef CPU_HPP
#define CPU_HPP

#include "Memory.hpp"
#include "Registers.hpp"
#include "Stack.hpp"
#include "Timers.hpp"
#include "Video.hpp"

namespace chip8
{
    class CPU
    {
    public:
        CPU() = default;

        /// \brief Clear the display
        /// \details Set the entire video buffer to zeroes
        void op00E0() noexcept;

        /// \brief Return from a subroutine
        /// \param[in] stack A reference to the stack containing instructions to execute
        /// \param[in] reg A reference to the register containing the program counter
        void op00EE() noexcept;

        /// \brief Jump to location nnn
        /// \details The interpreter sets the program counter to nnn
        void op1nnn() noexcept;

        /// \brief Call subroutine at nnn
        void op2nnn() noexcept;

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

        /// \brief DRW Vx, Vy, nibble
        /// \brief Display n-byte sprite starting at memory location I at (Vx, Vy) and set VF = collision
        void opDxyn() noexcept;

        /// \brief LD Vx, DT
        /// \brief Set Vx = delay timer value
        void opFx07() noexcept;

        /// \brief LD DT, Vx
        /// \brief Set the delay timer to Vx
        void opFx15() noexcept;

        /// \brief LD ST, Vx
        /// \brief Set sound timer = Vx
        void opFx18() noexcept;

        /// \brief LD B, Vx
        /// \brief Store BCD representation of Vx in memory locations I, I + 1, and I + 2
        /// \details The interpreter takes the decimal value of Vx and places the hundreds digit in memory at location I, 
        /// \details the tens digit at location I + 1, and the ones digit at location I + 2
        void opFx33() noexcept;

        /// \brief LD [I], Vx
        /// \brief Store registers V0 through Vx in memory starting at location I
        void opFx55() noexcept;

        /// \brief LD Vx, [I]
        /// \brief Read registers V0 through Vx from memory starting at location I
        void opFx65() noexcept;

    private:
        Memory memory_;
        Registers registers_;
        Stack stack_;
        Timers timers_;
        Video video_;
    };
}

#endif