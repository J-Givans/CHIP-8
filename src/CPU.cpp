#include "CPU.hpp"
#include "Instructions.hpp"

#include <cstdint>

#include <gsl/narrow>

namespace chip8
{
    void CPU::op00EE() noexcept
    {
        stack_.pop();
        registers_.setProgramCounter(stack_.top());
    }

    void CPU::opFx33() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t value = registers_[Vx];

        // 1s place
        memory_[gsl::narrow_cast<uint8_t>(registers_.getIndexRegister()) + 2] = value % 10;
        value /= 10;

        // 10s place
        memory_[gsl::narrow_cast<uint8_t>(registers_.getIndexRegister()) + 1] = value % 10;
        value /= 10;

        // 100s place
        memory_[gsl::narrow_cast<uint8_t>(registers_.getIndexRegister())] = value % 10;
    }

    void CPU::opFx55() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        for (uint8_t i = 0; i <= Vx; ++i) {
            uint8_t idx = gsl::narrow_cast<uint8_t>(registers_.getIndexRegister()) + i;
            memory_[idx] = registers_[i];
        }
    }

    void CPU::opFx65() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        for (uint8_t i = 0; i <= Vx; ++i) {
            uint8_t idx = gsl::narrow_cast<uint8_t>(registers_.getIndexRegister()) + i;
            registers_[i] = memory_[idx];
        }
    }
}