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
        /// \brief Default constructor
        CPU();

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

        /// \brief DRW Vx, Vy, nibble
        /// \brief Display n-byte sprite starting at memory location I at (Vx, Vy) and set VF = collision
        void opDxyn() noexcept;

        /// \brief SKP Vx
        /// \brief Skip the next instruction if the key with the value of Vx is pressed
        void opEx9E() noexcept;

        /// \brief SKNP Vx
        /// \brief Skip the next instruction if the key with the value of Vx is not pressed
        void opExA1() noexcept;

        /// \brief LD Vx, DT
        /// \brief Set Vx = delay timer value
        void opFx07() noexcept;

        /// \brief LD Vx, K
        /// \brief Wait for a key press, and then store the value of the key pressed in Vx
        void opFx0A() noexcept;

        /// \brief LD DT, Vx
        /// \brief Set the delay timer to Vx
        void opFx15() noexcept;

        /// \brief LD ST, Vx
        /// \brief Set sound timer = Vx
        void opFx18() noexcept;

        /// \brief ADD I, Vx
        /// \brief Set I = I + Vx
        void opFx1E() noexcept;

        /// \brief LD F, Vx
        /// \brief Set I = location of sprite for digit Vx
        void opFx29() noexcept;

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

        /// \brief Execute an instruction in table0
        void Table0();
        
        /// \brief Execute an instruction in table8
        void Table8();
        
        /// \brief Execute an instruction in tableE
        void TableE();
        
        /// \brief Execute an instruction in tableF
        void TableF();
        
        /// \brief Do nothing instruction
        void opNull();

    private:
        Memory memory_;
        Registers registers_;
        Stack stack_;
        Timers timers_;
        Video video_;

        using instruction = void (CPU::*)();

        std::array<instruction, 0xF + 1> table = {
            &CPU::Table0, &CPU::op1nnn, &CPU::op2nnn, &CPU::op3xkk,
            &CPU::op4xkk, &CPU::op5xy0, &CPU::op6xkk, &CPU::op7xkk,
            &CPU::Table8, &CPU::op9xy0, &CPU::opAnnn, &CPU::opBnnn,
            &CPU::opCxkk, &CPU::opDxyn, &CPU::TableE, &CPU::TableF
        };
        
        std::array<instruction, 0xE + 1> table0 = { &CPU::opNull };
        
        std::array<instruction, 0xE + 1> table8 = { 
            &CPU::op8xy0, &CPU::op8xy1, &CPU::op8xy2, &CPU::op8xy3, 
            &CPU::op8xy4, &CPU::op8xy5, &CPU::op8xy6, &CPU::op8xy7,
            &CPU::opNull, &CPU::opNull, &CPU::opNull, &CPU::opNull,
            &CPU::opNull, &CPU::opNull, &CPU::op8xyE
        };
        
        std::array<instruction, 0xE + 1> tableE = { &CPU::opNull };
        std::array<instruction, 0x65 + 1> tableF = { &CPU::opNull };
    };
}

#endif