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

        /// \brief Call subroutine at nnn
        void op2nnn() noexcept;

        /// \brief DRW Vx, Vy, nibble
        /// \brief Display n-byte sprite starting at memory location I at (Vx, Vy) and set VF = collision
        void opDxyn() noexcept;

        /// \brief LD Vx, DT
        /// \brief Set Vx = delay timer value
        void opFx07() noexcept;

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