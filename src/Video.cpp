#include "Video.hpp"
#include "Instructions.hpp"

namespace chip8
{
    void Video::opDxyn(Memory& memory, Registers& reg) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;
        uint8_t height = opcode & 0x000Fu;

        // Wrap if going beyond the screen boundaries
        uint8_t xPos = reg[Vx] % VideoWidth;
        uint8_t yPos = reg[Vy] % VideoHeight;

        reg[0xF] = 0;

        for (unsigned row = 0; row < height; ++row) {
            uint8_t spriteByte = memory.m_memory[reg.getIndexRegister() + row];

            for (unsigned col = 0; col < 8; ++col) {
                uint8_t spritePixel = spriteByte & (0x80u >> col);
                uint32_t* screenPixel = &videoBuffer[(yPos + row) * VideoWidth + (xPos + col)];

                if (spritePixel and *screenPixel == 0xFFFFFFFF) {
                    reg[0xF] = 1;
                }
                else if (spritePixel) {
                    *screenPixel ^= 0xFFFFFFFF;
                }
            }
        }
    }    
}