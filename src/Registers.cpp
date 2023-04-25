#include "Registers.hpp"
#include "Instructions.hpp"

namespace chip8
{
    void Registers::op1nnn() noexcept
    {
        // A jump doesn't remember its origin, so no stack interaction is required
        std::uint16_t address = opcode & 0x0FFFu;
        pc = address;
    }

    void Registers::op3xkk() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        if (byteRegisters[Vx] == byte) {
            pc += 2;
        }
    }

    void Registers::op4xkk() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        if (byteRegisters[Vx] != byte) {
            pc += 2;
        }
    }

    void Registers::op5xy0() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (byteRegisters[Vx] == byteRegisters[Vy]) {
            pc += 2;
        }
    }
}