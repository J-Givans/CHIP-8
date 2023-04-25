#include "Registers.hpp"
#include "Instructions.hpp"
#include "Keypad.hpp"

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

    void Registers::op8xy7() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (byteRegisters[Vy] > byteRegisters[Vx]) {
            byteRegisters[0xF] = 1;
        }
        else {
            byteRegisters[0xF] = 0;
        }

        byteRegisters[Vx] = byteRegisters[Vy] - byteRegisters[Vx];
    }

    void Registers::op8xyE() noexcept
    {
        // Perform a left shift and store the most significant bit in VF
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        // Save MSB in VF
        byteRegisters[0xF] = (byteRegisters[Vx] & 0x80u) >> 7u;
        
        byteRegisters[Vx] <<= 1;
    }

    void Registers::op9xy0() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t Vy = (opcode & 0x00F0u) >> 4u;

        if (byteRegisters[Vx] != byteRegisters[Vy]) {
            pc += 2;
        }
    }

    void Registers::opAnnn() noexcept
    {
        uint16_t address = opcode & 0x0FFFu;
        idxRegister = address;
    }

    void Registers::opBnnn() noexcept
    {
        uint16_t address = opcode & 0x0FFFu;
        pc = byteRegisters[0] + address;
    }

    void Registers::opCxkk() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t byte = opcode & 0x00FFu;

        byteRegisters[Vx] = distribution(generator) & byte;
    }

    void Registers::opEx9E() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t key = byteRegisters[Vx];

        if (KeyPad[key]) {
            pc += 2;
        }
    }

    void Registers::opExA1() noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        if (uint8_t key = byteRegisters[Vx]; not KeyPad[key]) {
            pc += 2;
        }
    }

    void Registers::opFx0A() noexcept
    {
        // Decrementing the pc by 2 whenever a key pad value is not detected
        // has the same effect as running the same instruction repeatedly.
        // This is the easiest way to wait

        if (uint8_t Vx = (opcode & 0x0F00u) >> 8u; KeyPad[0]) {
            byteRegisters[Vx] = 0;
        }
        else if (KeyPad[1]) {
            byteRegisters[Vx] = 1;
        }
        else if (KeyPad[2]) {
            byteRegisters[Vx] = 2;
        }
        else if (KeyPad[3]) {
            byteRegisters[Vx] = 3;
        }
        else if (KeyPad[4]) {
            byteRegisters[Vx] = 4;
        }
        else if (KeyPad[5]) {
            byteRegisters[Vx] = 5;
        }
        else if (KeyPad[6]) {
            byteRegisters[Vx] = 6;
        }
        else if (KeyPad[7]) {
            byteRegisters[Vx] = 7;
        }
        else if (KeyPad[8]) {
            byteRegisters[Vx] = 8;
        }
        else if (KeyPad[9]) {
            byteRegisters[Vx] = 9;
        }
        else if (KeyPad[10]) {
            byteRegisters[Vx] = 10;
        }
        else if (KeyPad[11]) {
            byteRegisters[Vx] = 11;
        }
        else if (KeyPad[12]) {
            byteRegisters[Vx] = 12;
        }
        else if (KeyPad[13]) {
            byteRegisters[Vx] = 13;
        }
        else if (KeyPad[14]) {
            byteRegisters[Vx] = 14;
        }
        else if (KeyPad[15]) {
            byteRegisters[Vx] = 15;
        }
        else {
            pc -= 2;
        }
    }
}