#include "Instructions.hpp"
#include "Memory.hpp"
#include "Video.hpp"
#include "Keypad.hpp"

#include <cstdint>

namespace chip8
{
    void opFx0A(Registers& reg) noexcept
    {
        reg.opFx0A();
    }

    void opFx1E(Registers& reg) noexcept
    {
        reg.opFx1E();
    }

    void opFx29(Registers& reg) noexcept
    {
        reg.opFx29();
    }
}