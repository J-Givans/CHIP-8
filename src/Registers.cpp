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
}