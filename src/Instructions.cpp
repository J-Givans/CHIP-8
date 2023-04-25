#include "Instructions.hpp"
#include "Memory.hpp"
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
        reg.op1nnn();
    }

    void op2nnn(Stack& stack, Registers& reg)
    {
        std::uint16_t address = opcode & 0x0FFFu;

        stack.push(reg.pc);
        reg.pc = address;
    }

    void op3xkk(Registers& reg) noexcept
    {
        reg.op3xkk();
    }

    void op4xkk(Registers& reg) noexcept
    {
        reg.op4xkk();
    }

    void op5xy0(Registers& reg) noexcept
    {
        reg.op5xy0();
    }

    void op6xkk(Registers& reg) noexcept
    {
        reg.op6xkk();
    }

    void op7xkk(Registers& reg) noexcept
    {
        reg.op7xkk();
    }

    void op8xy0(Registers& reg) noexcept
    {
        reg.op8xy0();
    }

    void op8xy1(Registers& reg) noexcept
    {
        reg.op8xy1();
    }

    void op8xy2(Registers& reg) noexcept
    {
        reg.op8xy2();
    }

    void op8xy3(Registers& reg) noexcept
    {
        reg.op8xy3();
    }

    void op8xy4(Registers& reg) noexcept
    {
        reg.op8xy4();
    }

    void op8xy5(Registers& reg) noexcept
    {
        reg.op8xy5();
    }

    void op8xy6(Registers& reg) noexcept
    {
        reg.op8xy6();
    }

    void op8xy7(Registers& reg) noexcept
    {
        reg.op8xy7();
    }

    void op8xyE(Registers& reg) noexcept
    {
        reg.op8xyE();
    }

    void op9xy0(Registers& reg) noexcept
    {
        reg.op9xy0();
    }

    void opAnnn(Registers& reg) noexcept
    {
        reg.opAnnn();
    }

    void opBnnn(Registers& reg) noexcept
    {
        reg.opBnnn();
    }

    void opCxkk(Registers& reg) noexcept
    {
        reg.opCxkk();
    }

    void opDxyn(Registers& reg, Memory& mem, Video& video)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;
        uint8_t height = opcode & 0x000Fu;

        // Wrap if going beyond the screen boundaries
        uint8_t xPos = reg.byteRegisters[Vx] % VideoWidth;
        uint8_t yPos = reg.byteRegisters[Vy] % VideoHeight;

        reg.byteRegisters[0xF] = 0;

        for (unsigned row = 0; row < height; ++row) {
            uint8_t spriteByte = mem.m_memory[reg.idxRegister + row];

            for (unsigned col = 0; col < 8; ++col) {
                uint8_t spritePixel = spriteByte & (0x80u >> col);
                uint32_t* screenPixel = &video.videoBuffer[(yPos + row) * VideoWidth + (xPos + col)];

                if (spritePixel and *screenPixel == 0xFFFFFFFF) {
                    reg.byteRegisters[0xF] = 1;
                }
                else if (spritePixel) {
                    *screenPixel ^= 0xFFFFFFFF;
                }
            }
        }
    }

    void opEx9E(Registers& reg) noexcept
    {
        reg.opEx9E();
    }

    void opExA1(Registers& reg) noexcept
    {
        reg.opExA1();
    }

    void opFx07(Registers& reg, CPU const& cpu)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        reg.byteRegisters[Vx] = cpu.delayTimer;
    }

    void opFx0A(Registers& reg) noexcept
    {
        reg.opFx0A();
    }

    void opFx15(Registers const& reg, CPU& cpu) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        cpu.delayTimer = reg.byteRegisters[Vx];
    }

    void opFx18(Registers& reg, CPU& cpu)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        cpu.soundTimer = reg.byteRegisters[Vx];
    }

    void opFx1E(Registers& reg) noexcept
    {
        reg.opFx1E();
    }

    void opFx29(Registers& reg)
    {
        // Font characters are located at address 0x50, and are 5 bytes each
        // We can therefore get the address of the first byte of each character by taking an offset from the start address

        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t digit = reg.byteRegisters[Vx];

        reg.idxRegister = FontSetStartAddress + (5 * digit);
    }

    void opFx33(Memory& memory, Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t value = reg.byteRegisters[Vx];

        // 1s place
        memory.m_memory[reg.idxRegister + 2] = value % 10;
        value /= 10;

        // 10s place
        memory.m_memory[reg.idxRegister + 1] = value % 10;
        value /= 10;

        // 100s place
        memory.m_memory[reg.idxRegister] = value % 10;
    }

    void opFx55(Memory& memory, Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        for (uint8_t i = 0; i <= Vx; ++i) {
            memory.m_memory[reg.idxRegister + i] = reg.byteRegisters[i];
        }
    }

    void opFx65(Memory const& memory, Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        for (uint8_t i = 0; i <= Vx; ++i) {
            reg.byteRegisters[i] = memory.m_memory[reg.idxRegister + i];
        }
    }
}