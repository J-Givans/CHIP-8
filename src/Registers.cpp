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

    void Registers::op6xkk() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        byteRegisters[Vx] = byte;
    }

    void Registers::op7xkk() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        byteRegisters[Vx] += byte;
    }

    void Registers::op8xy0() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        byteRegisters[Vx] = byteRegisters[Vy];
    }

    void Registers::op8xy1() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        byteRegisters[Vx] |= byteRegisters[Vy];
    }

    void Registers::op8xy2() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        byteRegisters[Vx] &= byteRegisters[Vy];
    }

    void Registers::op8xy3() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        byteRegisters[Vx] ^= byteRegisters[Vy];
    }

    void Registers::op8xy4() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;
        uint16_t sum = byteRegisters[Vx] + byteRegisters[Vy];

        if (sum > 255) {
            byteRegisters[0xF] = 1;
        }
        else {
            byteRegisters[0xF] = 0;
        }

        byteRegisters[Vx] = sum & 0xFFu;
    }

    void Registers::op8xy5() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (byteRegisters[Vx] > byteRegisters[Vy]) {
            byteRegisters[0xF] = 1;
        }
        else {
            byteRegisters[0xF] = 0;
        }

        byteRegisters[Vx] -= byteRegisters[Vy];
    }

    void Registers::op8xy6() noexcept
    {
        // Perform a right shift and set VF to the least significant bit
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        // Save LSB in VF
        byteRegisters[0xF] = (byteRegisters[Vx] & 0x1u);
        
        byteRegisters[Vx] >>= 1;
    }
}