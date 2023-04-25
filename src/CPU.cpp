#include "CPU.hpp"
#include "Instructions.hpp"

#include <cstdint>

#include <gsl/narrow>

namespace chip8
{
    CPU::CPU()
    {
        table0[0x0] = &CPU::op00E0;
        table0[0xE] = &CPU::op00EE;

        tableE[0x1] = &CPU::opExA1;
        tableE[0xE] = &CPU::opEx9E;

        tableF[0x07] = &CPU::opFx07;
        tableF[0x0A] = &CPU::opFx0A;
        tableF[0x15] = &CPU::opFx15;
        tableF[0x18] = &CPU::opFx18;
        tableF[0x1E] = &CPU::opFx1E;
        tableF[0x29] = &CPU::opFx29;
        tableF[0x33] = &CPU::opFx33;
        tableF[0x55] = &CPU::opFx55;
        tableF[0x65] = &CPU::opFx65;
    }

    void CPU::Table0()
    {
        // std::invoke(table0[opcode & 0x000Fu], this)?
        ((*this).*(table0[opcode & 0x000Fu]))();
    }

    void CPU::Table8()
    {
        ((*this).*(table8[opcode & 0x000Fu]))();
    }

    void CPU::TableE()
    {
        ((*this).*(tableE[opcode & 0x000Fu]))();
    }

    void CPU::TableF()
    {
        ((*this).*(tableF[opcode & 0x00FFu]))();
    }

    void CPU::opNull()
    {
        return;
    }

    void CPU::op00E0() noexcept
    {
        video_.clear();
    }

    void CPU::op00EE() noexcept
    {
        stack_.pop();
        registers_.setProgramCounter(stack_.top());
    }

    void CPU::op1nnn() noexcept
    {
        registers_.op1nnn();
    }

    void CPU::op2nnn() noexcept
    {
        std::uint16_t address = opcode & 0x0FFFu;

        stack_.push(registers_.getProgramCounter());
        registers_.setProgramCounter(address);
    }

    void CPU::op3xkk() noexcept
    {
        registers_.op3xkk();
    }

    void CPU::op4xkk() noexcept
    {
        registers_.op4xkk();
    }

    void CPU::op5xy0() noexcept
    {
        registers_.op5xy0();
    }

    void CPU::op6xkk() noexcept
    {
        registers_.op6xkk();
    }

    void CPU::op7xkk() noexcept
    {
        registers_.op7xkk();
    }

    void CPU::op8xy0() noexcept
    {
        registers_.op8xy0();
    }

    void CPU::op8xy1() noexcept
    {
        registers_.op8xy1();
    }

    void CPU::op8xy2() noexcept
    {
        registers_.op8xy2();
    }

    void CPU::op8xy3() noexcept
    {
        registers_.op8xy3();
    }

    void CPU::op8xy4() noexcept
    {
        registers_.op8xy4();
    }

    void CPU::op8xy5() noexcept
    {
        registers_.op8xy5();
    }

    void CPU::op8xy6() noexcept
    {
        registers_.op8xy6();
    }

    void CPU::op8xy7() noexcept
    {
        registers_.op8xy7();
    }

    void CPU::op8xyE() noexcept
    {
        registers_.op8xyE();
    }

    void CPU::op9xy0() noexcept
    {
        registers_.op9xy0();
    }

    void CPU::opAnnn() noexcept
    {
        registers_.opAnnn();
    }

    void CPU::opBnnn() noexcept
    {
        registers_.opBnnn();
    }

    void CPU::opCxkk() noexcept
    {
        registers_.opCxkk();
    }

    void CPU::opDxyn() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;
        uint8_t height = opcode & 0x000Fu;

        // Wrap if going beyond the screen boundaries
        uint8_t xPos = registers_[Vx] % VideoWidth;
        uint8_t yPos = registers_[Vy] % VideoHeight;

        registers_[0xF] = 0;

        for (unsigned row = 0; row < height; ++row) {
            uint8_t spriteByte = memory_[gsl::narrow_cast<uint8_t>(registers_.getIndexRegister() + row)];

            for (unsigned col = 0; col < 8; ++col) {
                uint8_t spritePixel = spriteByte & (0x80u >> col);
                uint32_t& screenPixel = video_[(yPos + row) * VideoWidth + (xPos + col)];

                if (spritePixel and screenPixel == 0xFFFFFFFF) {
                    registers_[0xF] = 1;
                }
                else if (spritePixel) {
                    screenPixel ^= 0xFFFFFFFF;
                }
            }
        }
    }

    void CPU::opEx9E() noexcept
    {
        registers_.opEx9E();
    }

    void CPU::opExA1() noexcept
    {
        registers_.opExA1();
    }

    void CPU::opFx07() noexcept
    {
        registers_.opFx07(timers_);
    }

    void CPU::opFx0A() noexcept
    {
        registers_.opFx0A();
    }

    void CPU::opFx15() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        timers_.delayTimer = registers_[Vx];
    }

    void CPU::opFx18() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        timers_.soundTimer = registers_[Vx];
    }

    void CPU::opFx1E() noexcept
    {
        registers_.opFx1E();
    }

    void CPU::opFx29() noexcept
    {
        registers_.opFx29();
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