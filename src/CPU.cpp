#include "CPU.hpp"
#include "Instructions.hpp"

#include <cstdint>

#include <gsl/narrow>

namespace chip8
{
    void CPU::op00E0() noexcept
    {
        video_.clear();
    }

    void CPU::op00EE() noexcept
    {
        stack_.pop();
        registers_.setProgramCounter(stack_.top());
    }

    void CPU::op2nnn() noexcept
    {
        std::uint16_t address = opcode & 0x0FFFu;

        stack_.push(registers_.getProgramCounter());
        registers_.setProgramCounter(address);
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

    void CPU::opFx07() noexcept
    {
        registers_.opFx07(timers_);
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