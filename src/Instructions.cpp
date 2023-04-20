#include "Instructions.hpp"
#include <cstdint>

namespace chip8
{
    constexpr void op00E0(Video& video) noexcept
    {
        video.clear();
    }

    void op00EE(Stack& stack, Registers& reg) noexcept
    {
        stack.pop();
        reg.pc = stack.top();
    }

    void op1nnn(Registers& reg) noexcept
    {
        // A jump doesn't remember its origin, so no stack interaction is required
        std::uint16_t address = opcode & 0x0FFFu;
        reg.pc = address;
    }

    void op2nnn(Stack& stack, Registers& reg)
    {
        std::uint16_t address = opcode & 0x0FFFu;

        stack.push(reg.pc);
        reg.pc = address;
    }

    void op3xkk(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        if (reg.registers[Vx] == byte) {
            reg.pc += 2;
        }
    }

    void op4xkk(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        if (reg.registers[Vx] != byte) {
            reg.pc += 2;
        }
    }

    void op5xy0(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (reg.registers[Vx] == reg.registers[Vy]) {
            reg.pc += 2;
        }
    }

    void op6xkk(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        reg.registers[Vx] = byte;
    }
}