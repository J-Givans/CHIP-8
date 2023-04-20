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

    void op7xkk(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        reg.registers[Vx] += byte;
    }

    void op8xy0(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        reg.registers[Vx] = reg.registers[Vy];
    }

    void op8xy1(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        reg.registers[Vx] |= reg.registers[Vy];
    }

    void op8xy2(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        reg.registers[Vx] &= reg.registers[Vy];
    }

    void op8xy3(Registers& reg) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        reg.registers[Vx] ^= reg.registers[Vy];
    }

    void op8xy4(Registers& reg) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;
        uint16_t sum = reg.registers[Vx] + reg.registers[Vy];

        if (sum > 255) {
            reg.registers[0xF] = 1;
        }
        else {
            reg.registers[0xF] = 0;
        }

        reg.registers[Vx] = sum & 0xFFu;
    }

    void op8xy5(Registers& reg) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (reg.registers[Vx] > reg.registers[Vy]) {
            reg.registers[0xF] = 1;
        }
        else {
            reg.registers[0xF] = 0;
        }

        reg.registers[Vx] -= reg.registers[Vy];
    }

    void op8xy6(Registers& reg) noexcept
    {
        // Perform a right shift and set VF to the least significant bit
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        // Save LSB in VF
        reg.registers[0xF] = (reg.registers[Vx] & 0x1u);
        
        reg.registers[Vx] >>= 1;
    }

    void op8xy7(Registers& reg) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (reg.registers[Vy] > reg.registers[Vx]) {
            reg.registers[0xF] = 1;
        }
        else {
            reg.registers[0xF] = 0;
        }

        reg.registers[Vx] = reg.registers[Vy] - reg.registers[Vx];
    }

    void op8xyE(Registers& reg) noexcept
    {
        // Perform a left shift and store the most significant bit in VF
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        // Save MSB in VF
        reg.registers[0xF] = (reg.registers[Vx] & 0x80u) >> 7u;
        
        reg.registers[Vx] <<= 1;
    }

    void op9xy0(Registers& reg) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (reg.registers[Vx] != reg.registers[Vy]) {
            reg.pc += 2;
        }
    }

    void opAnnn(Registers& reg) noexcept
    {
        uint16_t address = opcode & 0x0FFFu;
        reg.indexRegister = address;
    }

    void opBnnn(Registers& reg) noexcept
    {
        uint16_t address = opcode & 0x0FFFu;
        reg.pc = reg.registers[0] + address;
    }

    void opCxkk(Registers& reg) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        reg.registers[Vx] = distribution(generator) & byte;
    }
}