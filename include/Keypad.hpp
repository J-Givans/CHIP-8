#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include <array>
#include <cstdint>

namespace chip8
{
    inline std::array<uint8_t, 16> KeyPad = {
        0x1, 0x2, 0x3, 0xC,
        0x4, 0x5, 0x6, 0xD,
        0x7, 0x8, 0x9, 0xE,
        0xA, 0x0, 0xB, 0xF
    };
}

#endif