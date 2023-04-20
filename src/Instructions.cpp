#include "Instructions.hpp"
#include "Video.hpp"
#include "Keypad.hpp"

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

    void opDxyn(Registers& reg, Memory& mem, Video& video)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;
        uint8_t height = opcode & 0x000Fu;

        // Wrap if going beyond the screen boundaries
        uint8_t xPos = reg.registers[Vx] % VideoWidth;
        uint8_t yPos = reg.registers[Vy] % VideoHeight;

        reg.registers[0xF] = 0;

        for (unsigned row = 0; row < height; ++row) {
            uint8_t spriteByte = mem.m_memory[reg.indexRegister + row];

            for (unsigned col = 0; col < 8; ++col) {
                uint8_t spritePixel = spriteByte & (0x80u >> col);
                uint32_t* screenPixel = &video.videoBuffer[(yPos + row) * VideoWidth + (xPos + col)];

                if (spritePixel and *screenPixel == 0xFFFFFFFF) {
                    reg.registers[0xF] = 1;
                }
                else if (spritePixel) {
                    *screenPixel ^= 0xFFFFFFFF;
                }
            }
        }
    }

    void opEx9E(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t key = reg.registers[Vx];

        if (KeyPad[key]) {
            reg.pc += 2;
        }
    }

    void opExA1(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        if (uint8_t key = reg.registers[Vx]; not KeyPad[key]) {
            reg.pc += 2;
        }
    }

    void opFx07(Registers& reg, CPU const& cpu)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        reg.registers[Vx] = cpu.delayTimer;
    }

    void opFx0A(Registers& reg)
    {
        // Decrementing the pc by 2 whenever a key pad value is not detected
        // has the same effect as running the same instruction repeatedly.
        // This is the easiest way to wait

        if (uint8_t Vx = (opcode & 0x0F00u) >> 8u; KeyPad[0]) {
            reg.registers[Vx] = 0;
        }
        else if (KeyPad[1]) {
            reg.registers[Vx] = 1;
        }
        else if (KeyPad[2]) {
            reg.registers[Vx] = 2;
        }
        else if (KeyPad[3]) {
            reg.registers[Vx] = 3;
        }
        else if (KeyPad[4]) {
            reg.registers[Vx] = 4;
        }
        else if (KeyPad[5]) {
            reg.registers[Vx] = 5;
        }
        else if (KeyPad[6]) {
            reg.registers[Vx] = 6;
        }
        else if (KeyPad[7]) {
            reg.registers[Vx] = 7;
        }
        else if (KeyPad[8]) {
            reg.registers[Vx] = 8;
        }
        else if (KeyPad[9]) {
            reg.registers[Vx] = 9;
        }
        else if (KeyPad[10]) {
            reg.registers[Vx] = 10;
        }
        else if (KeyPad[11]) {
            reg.registers[Vx] = 11;
        }
        else if (KeyPad[12]) {
            reg.registers[Vx] = 12;
        }
        else if (KeyPad[13]) {
            reg.registers[Vx] = 13;
        }
        else if (KeyPad[14]) {
            reg.registers[Vx] = 14;
        }
        else if (KeyPad[15]) {
            reg.registers[Vx] = 15;
        }
        else {
            reg.pc -= 2;
        }
    }

    void opFx15(Registers const& reg, CPU& cpu) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        cpu.delayTimer = reg.registers[Vx];
    }

    void opFx18(Registers& reg, CPU& cpu)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        cpu.soundTimer = reg.registers[Vx];
    }

    void opFx1E(Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        reg.indexRegister += reg.registers[Vx];
    }
}