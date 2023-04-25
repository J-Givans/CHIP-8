#include "CPU.hpp"
#include "Instructions.hpp"

#include <cstdint>

#include <gsl/narrow>

namespace chip8
{
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